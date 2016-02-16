import os
import sys
import sqlite3


# Set the path to the path of this script

os.chdir(os.path.dirname(os.path.realpath(__file__)))


# Open our database file

connection = sqlite3.connect('~TEMP.db')
connection.row_factory = sqlite3.Row

c = connection.cursor()

c.execute('''SELECT * FROM parsed_declarations''')

entries = c.fetchall()


print "There are " + str(len(entries)) + " entries."


# Create an .html file to write to

f = open('index.html', 'w')
f.write('<head><link rel="stylesheet" type="text/css" href="docstyle.css"></head>')

for entry in entries:
    f.write('<h3>' + entry['name'] + '</h3>')
    f.write('<div class="doc">' + entry['object_str'] + '</div>')
    f.write('<div class="doc">' + entry['decl_string'] + '</div>')

f.close()
