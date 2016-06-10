#ifndef __AF_FILE_PATH
#define __AF_FILE_PATH




// wishlist
// have a std::vector<std::string, std::string> with special path locations
// project_path
// program_path
// system_path
// user_path
// etc...

// don't use a singleton

// implement a rescan

// swap out the functionality of find() and find_from() as appropriate

// make all functions operate with a FIND_LATEST flag or something




#include <string>
#include <vector>
#include <allegro5/allegro.h>




class Path
{
public:
   //private:
   static Path *instance;
   static void _recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder);
   static Path *get_instance();
   Path();

   static std::vector<ALLEGRO_PATH *> path;

public:
   static const char *find(std::string filename);
   static std::string find_from(std::string absolute_base_folder, std::string filename_to_find); // does not use an instance, only realtime recursive search.  Creates and destroys the whole file list each time.  //TODO make this more ideal
   static const char *find_latest(std::string filename);	// A convention I use frequently is to have the filename followed
   // by a space-dash-space " - " and then the two digit version
   // number.  You may see several files like this:
   // "this_is_my_filename - 01.txt"
   // "this_is_my_filename - 02.txt"
   // "this_is_my_filename - 03.txt"
   // all of them being the same file but the later numbered versions
   // are revisions of previous versions.
   // The function find_latest("this_is_my_filename - ##.txt") will
   // return the file matching the pattern with the largest
   // two-digit number.  This only works with two digits.
   // if no file is found, then "" is returned.

   static void str_out();
   static void rescan(); // untested

   ~Path();
};




#endif
