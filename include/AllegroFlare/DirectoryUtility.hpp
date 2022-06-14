#pragma once




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




namespace AllegroFlare
{
   class DirectoryUtility
   {
   private:
      bool initialized;
      std::string root_directory;
      ALLEGRO_PATH *root;
      std::vector<ALLEGRO_PATH *> path;
      bool sorted;

      void _recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder);
      int _bfind(std::string filename); // find with a binary search.  This will find *only* by the raw filename, and returns the index.

   public:
      DirectoryUtility(std::string root_directory="[directory-not-set]");
      ~DirectoryUtility();

      void initialize();
      const char *find(std::string filename);
      //TODO:: THIS FUNCTION find_all_versions WAS NEVER TESTED:
      std::vector<std::string> find_all_versions(std::string filename_pattern); // e.g. find_all_versions("this_is_my_filename - ##.txt");
      const char *bfind(std::string filename);
      const char *find_latest(std::string filename); // e.g. find_latest("this_is_my_filename - ##.txt");
      const char *bfind_latest(std::string filename_pattern); // under construction
      std::string dump();
      void rescan(); // untested
      int get_num_items();
      ALLEGRO_PATH *get_item(int index_num); // assumed read only, mkay? ;)
      std::string get_listing();
      std::string get_exe_path();
      std::string find_from(std::string absolute_base_folder, std::string filename_to_find); // does not use an instance, only realtime recursive search.  Creates and destroys the whole file list each time.  //TODO make this more ideal
   };




   // find_latest("this_is_my_filename - ##.txt");
   // A convention I use frequently is to have the filename followed
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
}




