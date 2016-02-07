import os
import sys
import sqlite3


# Set the path to the path of this script

os.chdir(os.path.dirname(os.path.realpath(__file__)))


# Open our database file

connection = sqlite3.connect('doc_entries.db')
connection.row_factory = sqlite3.Row

c = connection.cursor()

c.execute('''SELECT * FROM entries''')

entries = c.fetchall()


# Create an .html file to write to

f = open('index.html', 'w')
f.write('<head><link rel="stylesheet" type="text/css" href="docstyle.css"></head>')

for entry in entries:
    f.write('<h3>' + entry['decl'] + '</h3>')
    f.write('<pre class="code">' + entry['decl'] + '</pre>')
    f.write('<div class="doc">' + entry['documentation'] + '</div>')

f.close()
