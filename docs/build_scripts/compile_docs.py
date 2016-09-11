import os
import sys
import sqlite3
import cgi


# Set the path to the path of this script

os.chdir(os.path.dirname(os.path.realpath(__file__)))


# Open our database file

connection = sqlite3.connect('~TEMP.db')
connection.row_factory = sqlite3.Row

c = connection.cursor()


# Get a distinct list of parent names

c.execute('SELECT DISTINCT parent_name FROM parsed_declarations ORDER BY parent_name ASC;')

parent_names = c.fetchall()



# Create the full listings

cursor = c.execute('SELECT * FROM parsed_declarations')

entries = c.fetchall()
print "There are " + str(len(entries)) + " entries."

column_names = list(map(lambda x: x[0], cursor.description))



# Create an .html file to write to

f = open('../index.html', 'w')
f.write('<head><link rel="stylesheet" type="text/css" href="docstyle.css"></head>')

f.write('<ul>\n')
for parent_name in parent_names:
    f.write('  <li>' + parent_name[0] + '</li>\n')
f.write('</ul>\n')



# write the individual entries by sections

for parent_name in parent_names:

    parent_name_str = str(parent_name['parent_name'])

    f.write('<hr>\n')
    f.write('<h2>' + parent_name_str + '</h2>\n')

    cursor = c.execute('SELECT * FROM parsed_declarations WHERE parent_name=?', (parent_name_str,))
    entries = c.fetchall()

    for entry in entries:
        entry_name = entry['name']
        if entry['declaration_type'] == 'member function': entry_name = '.' + entry_name + '()'
        declaration = cgi.escape(entry['declaration'])
        in_source_documentation = cgi.escape(entry['in_source_documentation'])

        f.write('<div class="listing_container">\n')
        f.write('<h3>' + entry_name + '</h3>\n')
        f.write('<p>' + in_source_documentation + '</p>\n')
        f.write('<pre class="code">' + declaration + '</pre>\n')
        f.write('</div>\n')
        f.write('<table class="comprehensive">\n')
        for column_name in column_names:
            column_value = cgi.escape(str(entry[column_name]))
            f.write('<tr><td>' + column_name + '</td><td>' + column_value + '</td></tr>\n')
        f.write('</table>\n')
        f.write('\n')



# close the file

f.close()
