import os
import sys
import glob
import sqlite3
import re

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser


# Set the path to the path of this script
os.chdir(os.path.dirname(os.path.realpath(__file__)))


from terminal_color_output import *




# The c++ file we want to parse
# filename_file = sys.argv[1]
# filename = "../include/allegro_flare/" + filename_file

'''
create_entries_query = """
CREATE TABLE IF NOT EXISTS entries(
    id INTEGER PRIMARY KEY,
    decl VARCHAR(128),
    description TEXT
    );
"""
'''
#make_table_connection.execute(create_entries_query)

create_query = """
CREATE TABLE parsed_declarations(
           id INTEGER PRIMARY KEY,
           object_str VARCHAR(255),
           decl_string VARCHAR(255),
           name VARCHAR(128),
           declaration_type VARCHAR(32),
           parent_name VARCHAR(64),
           top_parent_name VARCHAR(64),
           attributes VARCHAR(255),
           header_file VARCHAR(255),
           line_number INTEGER,
           in_source_documentation TEXT,
           documentation TEXT
           );
"""

parse_cache_connection = sqlite3.connect('~TEMP.db')
# connection.row_factory = sqlite3.Row
parse_cache_make_table_connection = parse_cache_connection.cursor()
parse_cache_make_table_connection.execute("DROP TABLE IF EXISTS parsed_declarations;")
parse_cache_make_table_connection.execute(create_query)

parse_cache_connection.commit()



def parse_file(filename):
    # Find the location of the xml generator (castxml or gccxml)
    generator_path, generator_name = utils.find_xml_generator(name='castxml')

    # Configure the xml generator
    xml_generator_config = parser.xml_generator_configuration_t(
        # cflags="-std=gnu++11",
        cflags="-Wno-c++11-extensions",
        include_paths=["/Users/markoates/Repos/allegro_flare/include"],
        xml_generator_path=generator_path,
        compiler="g++",
        xml_generator=generator_name)

    # Parse the c++ file
    decls = parser.parse([filename], xml_generator_config)


    # output some GOLD!

    global_namespace = declarations.get_global_namespace(decls)

    # Search for functions which return a double. Two functions will be found
    criteria = declarations.calldef_matcher(
         #return_type="float",
         #header_file="/Users/markoates/Repos/allegro_flare/include/allegro_flare/" + filename)
         header_file=os.path.abspath(filename))
    # criteria = declarations.calldef_matcher(return_type=double_type)

    found_items = declarations.matcher.find(criteria, global_namespace)



    # populate the table with unique names

    count = 0
    for item in found_items:
        count = count + 1 
        #print item.location.file_name + " : " + str(item.location.line)
        cleaned_filename = re.match(r'/Users/markoates/Repos/allegro_flare/(.*)', item.location.file_name).group(1)

        declaration_type = item.__class__.__name__
        if declaration_type[-2:] == "_t":
            declaration_type = declaration_type[:-2]
        declaration_type = declaration_type.replace('_', ' ')
        declaration_type = "%s" % declaration_type

        parse_cache_make_table_connection.execute("INSERT INTO parsed_declarations VALUES (NULL,?,?,?,?,?,?,?,?,?,?,?);",
            (str(item), item.decl_string, item.name, declaration_type, str(item.parent.name), str(item.top_parent.name), item.attributes, cleaned_filename, str(item.location.line), "", "")
            )
        parse_cache_connection.commit()

    # create a list of unique items

    unique_item_names = set();
    for item in found_items:
        unique_item_names.update({item.name})


    # cross-correlate declarations in the database

    docs_connection = sqlite3.connect('doc_entries.db')
    docs_connection.row_factory = sqlite3.Row
    docs_c = docs_connection.cursor()


    found_items = 0
    unfound_items = 0

    for item in unique_item_names:
        docs_c.execute('SELECT * FROM entries WHERE decl=?', (item, ))
        entries = docs_c.fetchall()
        if len(entries) == 0:
            print item
            unfound_items += 1
        else:
            print_green(item + " - FOUND")
            found_items += 1

    if unfound_items == 0:
        print_func = print_green
    elif found_items == 0:
        print_func = print_red
    else:
        print_func = print_yellow

    print_func("==============================")
    print_func(str(found_items) + " items found.")
    print_func(str(unfound_items) + " matches missing.")
    print_func("==============================")

    return




# get a file list
header_files = glob.glob("../../include/allegro_flare/*/*/*.h")
header_files += glob.glob("../../include/allegro_flare/*/*.h")
header_files += glob.glob("../../include/allegro_flare/*.h")


count = 0
num_header_files = len(header_files) 
for f in header_files:
    count = count + 1
    print "===== parsing " + str(count) + " of " + str(num_header_files) + " ====="
    parse_file(f)
