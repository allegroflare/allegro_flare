import os
import sys
import sqlite3

from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser


# Set the path to the path of this script
os.chdir(os.path.dirname(os.path.realpath(__file__)))


# Find the location of the xml generator (castxml or gccxml)
generator_path, generator_name = utils.find_xml_generator(name='castxml')


# Configure the xml generator
xml_generator_config = parser.xml_generator_configuration_t(
    # cflags="-std=gnu++11",
    include_paths=["/Users/markoates/Repos/allegro_flare/include"],
    xml_generator_path=generator_path,
    compiler="gcc",
    xml_generator=generator_name)


# The c++ file we want to parse
filename = "../include/allegro_flare/useful.h"


# Parse the c++ file
decls = parser.parse([filename], xml_generator_config)



# output some GOLD!

global_namespace = declarations.get_global_namespace(decls)

# Search for functions which return a double. Two functions will be found
criteria = declarations.calldef_matcher(
     #return_type="float",
     header_file="/Users/markoates/Repos/allegro_flare/include/allegro_flare/useful.h")
# criteria = declarations.calldef_matcher(return_type=double_type)

found_items = declarations.matcher.find(criteria, global_namespace)



# create a unique list of declaration names

unique_item_names = set();

for item in found_items:
    unique_item_names.update({item.name})

for item in unique_item_names:
    print item


