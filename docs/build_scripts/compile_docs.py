import os
import sys
import sqlite3


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

cursor = c.execute('SELECT * FROM parsed_declarations WHERE parent_name=?', ('UISurfaceAreaBitmapAlpha',))

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

for entry in entries:
    f.write('<h3>' + entry['name'] + '</h3>\n')
    f.write('<table class="comprehensive">\n')
    for column_name in column_names:
        f.write('<tr><td>' + column_name + '</td><td>' + str(entry[column_name]) + '</td></tr>\n')
    f.write('</table>\n')
    f.write('\n')

f.close()
