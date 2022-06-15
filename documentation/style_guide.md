# AllegroFlare Style Guide


Note: Several components under [`quintessence/`](https://github.com/allegroflare/allegro_flare/tree/master/quintessence
) are automatically formatted from the
[`quintessence_from_yaml`](https://github.com/MarkOates/blast/blob/master/programs/quintessence_from_yaml.cpp) program and its related components.  They, along with manually created files, generally should follow the following style:


## Main Style Points

- Unix file format
- 3 spaces for indentation
- lines no longer than 120 characters
- opening `{` braces on separate line, at same indentation as preceeding statement
- avoid single-line `if` statements (for readability)
- No spaces within parenthesis
- Prefer paces between operators `+`, `-`, `*`, `/`, etc., except when in `for (;;)`
- Use `override` on all overriding functions
- Prefer range-based for loops `for (:)` over `for (;;)` when iterating over collections
- Use `nullptr` over `NULL` or `0`
- Prefer using a `NO_FLAGS` constant (or similar) over `0` when passing empty flags to allegro functions.
- `#include` directives should be ordered with more generic headers first (.e.g stdlib header files), then more specific header files (allegro header files), then `AllegroFlare` headers.  The exception is in `.cpp` source files, where the component's `#include` is listed as the first item, followed by a blank line.

## Comments `//`

- no multiline `/* comments /*`; Prefer multiple lines of `//` comments
- no comments-as-documentation. (Some currently exist in legacy code. They should be removed and proper documentation added).
- no "functional" comments (comments that include `num_spaces=3` for formatting, for example)
- comments may be used as a way to visually separate sections in a function for clarity
- comments may be used for clarity and/or development notes


## File Type Specific Formatting

### Quintessence Files

- 2 blank-lines between sections

### Header Files (either generated or manual)

- `#pragma once` on top line
- 2 blank-lines between sections (list of `#include` files, list of `#define` statements, etc)
- All namespaces indent their encapsulated code
- namespace closing `}` braces accompanied by `// namespace NameOfNamespace` comment
- 2 blank-lines at end of file

### Source Files (either generated or manual)

- 2 blank-lines at top
- `#include` directive for the component
- 2 blank-lines between sections (list of `#include` files, list of `#define` statements, etc)
- 2 blank-lines between each function definition
- namespaces do not indent their encapsulated code. Declarations are all at the same left-most level of indentation (column 1), so definitions do not require extra indentation.
- namespace closing `}` braces accompanied by `// namespace NameOfNamespace` comment
- 2 blank-lines at end of file

### Test Files

- 2 blank-lines at top
- gtest `#include` statements and related macros declared first, and considered a separate section from the other `#include` directives
- 2 blank-lines between sections (list of `#include` files, list of `#define` definitions, definitions of test classes, etc)
- Name of the gtest "test class" follows the format `ComponentNamespace_ComponentNameTest`. It's the component name and its namespaces separated by `_`, along with the word `Test` appended
- Most tests should test a single specific behavior of a single function of the class.  The format for these test names is `[name_of_function]__[does_the_expected_thing]`, where `[name_of_function]` is the name of the class function being tested, and `[does_the_expected_thing]` is an active-voice, explicit expected behavior being tested
- Don't test multiple cases in a single test



