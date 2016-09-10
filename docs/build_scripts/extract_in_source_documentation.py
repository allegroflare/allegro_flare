



# In AllegroFlare, it is preferible to have a concice, brief
# comment above declarations in the source code itself.  This
# comment serves two purposes:
#
# 1) Give a nice quick reference to anybody browsing the source
#    code directly.
# 2) Create a 'briefest, simplest' comment that is also used in
#    the documentation.
#
# These 'mini-comments' will always appear above the declaration
# with the C++ single-line comment // format, and could be
# multiple lines or multiple sentences.




def extract_in_source_documentation(filename, declaration_line_number):
    # 1) open the file in question

    file_pointer = file(filename, 'r')

    # 2) grab all the lines in the file and put them into an array

    file_lines = file_pointer.readlines()
    extracted_comment = ''

    # 3) go to the preceeding line.  If this preceeding line
    #    begins with '//', then prepend the contents of that line
    #    to the final comment.  If there is not a commented '//'
    #    line, then proceed to step 5.

    # 4) repeat step 3 to see if there is another preceeding
    #    line of '//' comments.  If there are no more '//' lines
    #    left, then proceed to step 5.

    current_line_number = declaration_line_number - 1 - 1
    line = file_lines[current_line_number].strip()

    while line[:2] == '//':
        extracted_comment = line[2:] + extracted_comment
        current_line_number = current_line_number - 1
        line = file_lines[current_line_number].strip()

    # 5) Return the final extracted comment

    return extracted_comment




