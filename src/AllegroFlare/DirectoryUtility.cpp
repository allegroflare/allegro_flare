



#include <AllegroFlare/DirectoryUtility.hpp>

#include <algorithm>
#include <iostream>
#include <locale>
#include <sstream>
//#include <allegro_flare/profile_timer.h>




namespace AllegroFlare
{
   static bool __is_number(const std::string& s)
   {
      std::locale loc;
      std::string::const_iterator it = s.begin();
      while (it != s.end() && std::isdigit(*it, loc)) ++it;
      return !s.empty() && it == s.end();
   }



   std::string DirectoryUtility::get_exe_path()
   {
      ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      std::string p = al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP);
      al_destroy_path(resource_path);
      return p;
   }



   static bool path_filename_comp(const ALLEGRO_PATH *p1, const ALLEGRO_PATH *p2)
   {
      return strcmp(al_get_path_filename(p1), al_get_path_filename(p2)) < 0;
   }




   void DirectoryUtility::_recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder)
   {
      if (al_open_directory(folder))
      {
         ALLEGRO_FS_ENTRY *file;

         while ((file=al_read_directory(folder)))
         {
            const char *filename = al_get_fs_entry_name(file);
            if (al_get_fs_entry_mode(file) & ALLEGRO_FILEMODE_ISDIR)
            {
               ALLEGRO_FS_ENTRY *nested_folder = al_create_fs_entry(filename);
               _recursive_traverse_dir(nested_folder);
            }
            else
            {
               path.push_back(al_create_path(filename));
            }
         }

         al_close_directory(folder);
      }
   }




   static void __recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder, std::vector<ALLEGRO_PATH *> *path)
   {
      if (al_open_directory(folder))
      {
         ALLEGRO_FS_ENTRY *file;

         while ((file=al_read_directory(folder)))
         {
            const char *filename = al_get_fs_entry_name(file);
            if (al_get_fs_entry_mode(file) & ALLEGRO_FILEMODE_ISDIR)
            {
               ALLEGRO_FS_ENTRY *nested_folder = al_create_fs_entry(filename);
               //std::cout << "found folder " << al_get_fs_entry_name(nested_folder) << std::endl;
               __recursive_traverse_dir(nested_folder, path);
            }
            else
            {
               //std::cout << "found path " << al_get_fs_entry_name(file) << std::endl;
               path->push_back(al_create_path(filename));
            }
         }

         al_close_directory(folder);
      }
   }



   void DirectoryUtility::initialize()
   {
      initialized = true;

      // store the current directory
      std::string current_directory = al_get_current_directory();

      // create the FS_ENTRY
      root = al_create_path(root_directory.c_str());
      if (!root)
      {
         std::cout << __FUNCTION__ << ": cannot create dir tree with \"" << root_directory << "\"" << std::endl;
         return;
      }
      //start_profile_timer("indexing");
      std::cout << "Indexing...";
      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(al_path_cstr(root, ALLEGRO_NATIVE_PATH_SEP));

      _recursive_traverse_dir(folder);
      //stop_profile_timer("indexing");
      //std::cout << "finished. Took " << get_profile_timer_length("indexing") << " seconds. " << get_num_items() << " items found." << std::endl;

      std::cout << "Sorting...";
      //start_profile_timer("sorting");
      std::sort(path.begin(), path.end(), path_filename_comp);
      //stop_profile_timer("sorting");
      //std::cout << "finished. Took " << get_profile_timer_length("sorting") << " seconds. " << get_num_items() << " items found." << std::endl;
      sorted = true;
      al_destroy_fs_entry(folder);

      // restore the directory before this constructor
      al_change_directory(current_directory.c_str());
   }



   DirectoryUtility::DirectoryUtility(std::string root_directory)
      : initialized(false)
      , root_directory(root_directory)
      , root(NULL)
      , path()
      , sorted(false)
   {}




   std::string DirectoryUtility::get_listing()
   {
      std::stringstream ss;
      for (unsigned i=0; i<path.size(); i++)
      {
         //if (filename == al_get_path_filename(path[i]))
         //	return al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP);
         ss << al_get_path_filename(path[i]) << "\t" << al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP) << "\n";
      }
      return ss.str();
   }




   const char *DirectoryUtility::find(std::string filename)
      // returns the full file path from the current directory
      // this could be made more efficient with a binary search
   {
      for (unsigned i=0; i<path.size(); i++)
         if (filename == al_get_path_filename(path[i]))
            return al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP);
      return "";
   }




   int DirectoryUtility::_bfind(std::string filename)
   {
      int comp, first, last, mid;
      const char *cc_filename = filename.c_str();

      first = 0;
      last = path.size();

      while (first <= last)
      {
         mid = (first + last) / 2;  // compute mid point.
         comp = strcmp(al_get_path_filename(path[mid]), cc_filename);

         if (comp < 0)
            first = mid + 1;  // repeat search in top half.
         else if (comp > 0)
            last = mid - 1; // repeat search in bottom half.
         else
            return mid;     // found it. return position
      }
      return -1;
   }




   const char *DirectoryUtility::bfind(std::string filename)
   {
      int found = _bfind(filename);
      if (found == -1) return "";
      return al_path_cstr(path[found], ALLEGRO_NATIVE_PATH_SEP);
   }




   // returns the full file path from the current directory
   // this could be made more effecient with a binary search
   std::string DirectoryUtility::find_from(std::string absolute_base_folder, std::string filename_to_find)
   {
      std::vector<ALLEGRO_PATH *> localy_found_paths;


      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(absolute_base_folder.c_str());
      __recursive_traverse_dir(folder, &localy_found_paths);
      std::sort(localy_found_paths.begin(), localy_found_paths.end(), path_filename_comp);
      al_destroy_fs_entry(folder);


      for (unsigned i=0; i<localy_found_paths.size(); i++)
      {
         if (filename_to_find == al_get_path_filename(localy_found_paths[i]))
         {
            // grab that found file's full path
            std::string return_str = al_path_cstr(localy_found_paths[i], ALLEGRO_NATIVE_PATH_SEP);

            // destroy the discovered paths
            for (unsigned p=0; p<localy_found_paths.size(); p++)
               al_destroy_path(localy_found_paths[p]);

            return return_str.c_str();
         }
      }

      // destroy the discovered paths
      for (unsigned p=0; p<localy_found_paths.size(); p++)
         al_destroy_path(localy_found_paths[p]);

      return "";
   }




   const char *DirectoryUtility::bfind_latest(std::string filename_pattern)
   {
      std::cout << __FUNCTION__ << " is under construction.  Switching to find_latest()" << std::endl;
      return find_latest(filename_pattern);
   }




   std::vector<std::string> DirectoryUtility::find_all_versions(std::string filename)
   {
      std::string path_to_return = "";
      size_t n = std::count(filename.begin(), filename.end(), '#');
      std::size_t pos_of_2_pounds = filename.find("##");
      std::vector<std::string> matches;

      if (n != 2 || pos_of_2_pounds == std::string::npos)
      {
         std::cout << "DirectoryUtility::find_latest(\"" << filename << "\") does not contain 2 ajacent # signs (##)" << std::endl;
         std::cout << "\tswitching to DirectoryUtility::find(\"" << filename << "\")" << std::endl;
         return matches;
         //return find(filename);
      }




      std::string filename_front_part = filename.substr(0, pos_of_2_pounds);
      std::string filename_back_part = filename.substr(pos_of_2_pounds+2);

      for (unsigned i=0; i<path.size(); i++)
      {
         std::string filename_to_test = al_get_path_filename(path[i]);

         // make sure the non-wildcard components match
         std::string filename_to_test_front_part = filename_to_test.substr(0, pos_of_2_pounds);
         if (filename_to_test_front_part != filename_front_part) continue;

         std::string filename_to_test_back_part = filename_to_test.substr(pos_of_2_pounds+2);
         if (filename_to_test_back_part != filename_back_part) continue;

         std::string filename_number_part = filename_to_test.substr(pos_of_2_pounds, 2);
         if (!__is_number(filename_number_part)) continue;

         // At this point we have a positive match.  Now just check the number.
         matches.push_back(al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP));
         //int number_of_filename_to_test = atoi(filename_number_part.c_str());

         //if (number_of_filename_to_test > largest_number_found)
         //{
         //	largest_number_found = number_of_filename_to_test;
         //	index_of_largest_number_found = i;
         //}
      }

      // if a match was found, return the found path.
      //if (index_of_largest_number_found != -1)
      //	return al_path_cstr(path[index_of_largest_number_found], ALLEGRO_NATIVE_PATH_SEP);

      // otherwise, return the empty string.
      //return "";
      return matches;
   }




   //TODO: make a bfind_latest
   // find_latest doest not emplore a binary search, it's linear.
   // it's also slow because it needs to al_get_path_filename, substr, cmp, substr, cmp, isnumber, for each file.
   // make a bfind_latest
   const char *DirectoryUtility::find_latest(std::string filename)
   {
      //	get_instance();

      std::string path_to_return = "";
      size_t n = std::count(filename.begin(), filename.end(), '#');
      std::size_t pos_of_2_pounds = filename.find("##");
      if (n != 2 || pos_of_2_pounds == std::string::npos)
      {
         std::cout << "DirectoryUtility::find_latest(\"" << filename << "\") does not contain 2 ajacent # signs (##)" << std::endl;
         std::cout << "\tswitching to DirectoryUtility::find(\"" << filename << "\")" << std::endl;
         return find(filename);
      }

      std::string filename_front_part = filename.substr(0, pos_of_2_pounds);
      std::string filename_back_part = filename.substr(pos_of_2_pounds+2);

      int largest_number_found = -1;
      int index_of_largest_number_found = -1;
      for (unsigned i=0; i<path.size(); i++)
      {
         std::string filename_to_test = al_get_path_filename(path[i]);

         // make sure the non-wildcard components match
         std::string filename_to_test_front_part = filename_to_test.substr(0, pos_of_2_pounds);
         if (filename_to_test_front_part != filename_front_part) continue;

         std::string filename_to_test_back_part = filename_to_test.substr(pos_of_2_pounds+2);
         if (filename_to_test_back_part != filename_back_part) continue;

         std::string filename_number_part = filename_to_test.substr(pos_of_2_pounds, 2);
         if (!__is_number(filename_number_part)) continue;

         // At this point we have a positive match.  Now just check the number.
         int number_of_filename_to_test = atoi(filename_number_part.c_str());

         if (number_of_filename_to_test > largest_number_found)
         {
            largest_number_found = number_of_filename_to_test;
            index_of_largest_number_found = i;
         }
      }

      // if a match was found, return the found path.
      if (index_of_largest_number_found != -1)
         return al_path_cstr(path[index_of_largest_number_found], ALLEGRO_NATIVE_PATH_SEP);

      // otherwise, return the empty string.
      return "";
   }




   int DirectoryUtility::get_num_items()
   {
      return path.size();
   }




   ALLEGRO_PATH *DirectoryUtility::get_item(int index_num)
   {
      if (index_num < 0 || path.empty() || index_num >= (int)path.size()) return NULL;
      return path[index_num];
   }




   DirectoryUtility::~DirectoryUtility()
   {
      for (unsigned i=0; i<path.size(); i++)
         al_destroy_path(path[i]);
   }




   std::string DirectoryUtility::dump()
   {
      std::stringstream result;
      for (unsigned i=0; i<path.size(); i++)
      {
         result << al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP) << std::endl;
      }
      return result.str();
   }




   void DirectoryUtility::rescan()
   {
      //get_instance();

      // clean out the previous
      for (unsigned i=0; i<path.size(); i++)
         al_destroy_path(path[i]);

      // repopulate
      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(".");
      _recursive_traverse_dir(folder);
      std::sort(path.begin(), path.end(), path_filename_comp);
      al_destroy_fs_entry(folder);
   }




   //PathObject *PathObject::instance = NULL;
   //std::vector<ALLEGRO_PATH *> PathObject::path;
}



