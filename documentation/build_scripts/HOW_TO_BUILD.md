# How To Build the AllegroFlare Documentation

### Technologies

Documentation is generated with a few python scripts in the `documentation/` folder.  To run them, you will need `Python`, `pygccxml` (with a `CASTXML` backend), and `sqlite`.

### Process

The first script will parse through all of the AllegroFlare source code and generate a `~TEMP.db` file.  This is a relatively lengthly process and can take a cocuple of minutes, so this is something to prepare for.  The `~TEMP.db` database is an SQL file with nicely broken down class names, function names, line info, and a bunch of other useful deconstructions of the AllegroFlare source code.  Run the script by entering the following command in the terminal:

```
$ python documentation/build_scripts/parse_source.py
```

Once the `~TEMP.db` file has been created, you can generate a more friendly HTML document with the `compile_documentation.py` script.  Use the following command:

```
$ python documentation/build_scripts/compile_documentation.py
```

This will generate the acutal HTML documentation files from the content that exists in `~TEMP.db`.

### In the future

In the future, the database file `doc_entries.db` will contain extended definitions and descriptions for use in the documentation that do not otherwise belong in the source itself.  There will also be a script to validate that entries in `~TEMP.db` and entries in `doc_entries.db` are in sync - none are missing, no typos, etc.
