# AllegroFlare Docs Project

### What do you want to make?

A simple, comprehensive project that makes documenting code for AllegroFlare fun, easy, and achievable.  The tool(s) made shouldn't be too abstract, they can be talor-fit to AllegroFlare's codebase and style.

### What technology will you use?

Primarily written with Python scripts, tasks coordinated with `Makefile`s, and code parsed with some pretty powerful 3rd party parsing tools.  Parsing will be done with `pygccxml` along with either the `gccxml` backend (which is a depreciated project) or the more modern `CastXML` backend.  Documentation entries will be stored in an SQL database, probably managed by `sqlite`. Python scripts and SQL database files will reside in the AllegroFlare repo.

### What features will it use?

The documentation itself should include a well-organized index, a search feature, cross linking on all function names, link to source/file/line location on the github repo, offer some related functions, group functions and classes in a logical way that doesn't have to be strictly adherent to the way the code is organized internally.  Doc might have helpful images and possibly code examples as well.

As for using the actual tools for the project, documentation will self-build as a `make` task that will invoke the python scripts. The scripts will cross-corrolate the parsed code with the SQL database, report any inconsistencies, and then build HTML documentation with a combination of the SQL file and extracted parse data.

### What features _must_ it include?

The documentation must be decouped from the source code.  There should be no 'documentation droppings' inside the code itself.  The documentation format and design will be clean, unique, and modern.  Each AllegroFlare class, namespace, function, etc. will have an entry in the documentation, and each entry must be visible and accessible.

### How will you implement it?

Development of the project will be broken down into several sub-tasks.

##### Phase 0. Discovery - COMPLETE
+ Explore possible options for documentation
+ Decide which approach is best
+ Write project summary (this document)

##### Phase 1. Setup
+ Build and setup the necessairy tools/dependencies/workflow
+ Verify/update the codebase is parsable and reachable
+ Create and output an initial parse of the codebase

##### Phase 2. Populate the database
+ Create a SQL database with a list of declarations that should have entries and declarations that should be ignored
+ Create a batch process that validates existing entries and finds entries that are not accounted for
+ Begin the process of writing the documentation

##### Phase 3. Publish and format as HTML
+ Create a stylesheet and initial HTML template for the documentation
+ Create a technique that compiles the SQL and parse data into the HTML format
+ Publish the documentation online

### What's your timeline?

No deadlines are imposed on this project.  It will progress as time allows.  Would like to have a working v1 ready in 2 months, March 31 2016.
