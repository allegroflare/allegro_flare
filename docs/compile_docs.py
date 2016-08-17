import os
import sys
import sqlite3


# Set the path to the path of this script

os.chdir(os.path.dirname(os.path.realpath(__file__)))


# Open our database file

connection = sqlite3.connect('~TEMP.db')
connection.row_factory = sqlite3.Row

c = connection.cursor()

cursor = c.execute('''SELECT * FROM parsed_declarations''')

entries = c.fetchall()
print "There are " + str(len(entries)) + " entries."

column_names = list(map(lambda x: x[0], cursor.description))


# Create an .html file to write to

f = open('index.html', 'w')
f.write('<head><link rel="stylesheet" type="text/css" href="docstyle.css"></head>')

for entry in entries:
    f.write('<h3>' + entry['name'] + '</h3>')
    f.write('<table class="comprehensive">')
    for column_name in column_names:
        f.write('<tr><td>' + column_name + '</td><td>' + str(entry[column_name]) + '</td></tr>')
    f.write('</table>')

f.close()
