



#include <allegro_flare/file_path.h>

#include <algorithm>
#include <iostream>
#include <locale>




namespace allegro_flare
{
   static bool __is_number(const std::string& s)
   {
      std::locale loc;
      std::string::const_iterator it = s.begin();
      while (it != s.end() && std::isdigit(*it, loc)) ++it;
      return !s.empty() && it == s.end();
   }




   static bool path_filename_comp(const ALLEGRO_PATH *p1, const ALLEGRO_PATH *p2)
   {
      return strcmp(al_get_path_filename(p1), al_get_path_filename(p2)) < 0;
   }




   void Path::_recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder)
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




   Path::Path()
   {
      if (!al_is_system_installed()) std::runtime_error("Cannot create Path object: Allegro is not initialized");
      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(".");
      _recursive_traverse_dir(folder);
      std::sort(path.begin(), path.end(), path_filename_comp);
      al_destroy_fs_entry(folder);
   }




   Path *Path::get_instance()
   {
      if (!instance) instance = new Path();
      return instance;
   }




   // returns the full file path from the current directory
   // this could be made more effecient with a binary search
   const char *Path::find(std::string filename)
   {
      get_instance();

      for (unsigned i=0; i<path.size(); i++)
         if (filename == al_get_path_filename(path[i]))
            return al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP);
      return "";
   }




   void __recursive_traverse_dir(ALLEGRO_FS_ENTRY *folder, std::vector<ALLEGRO_PATH *> *path)
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




   //#include <allegro_flare/profile_timer.h>




   // returns the full file path from the current directory
   // this could be made more effecient with a binary search
   std::string Path::find_from(std::string absolute_base_folder, std::string filename_to_find)
   {
      std::vector<ALLEGRO_PATH *> localy_found_paths;


      //start_profile_timer("find_from");
      //std::cout << "+ finding file in directory tree..." << std::endl;
      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(absolute_base_folder.c_str());
      __recursive_traverse_dir(folder, &localy_found_paths);
      std::sort(localy_found_paths.begin(), localy_found_paths.end(), path_filename_comp);
      al_destroy_fs_entry(folder);
      //stop_profile_timer("find_from");
      //std::cout << "+ finished (" << get_profile_timer_length("find_from") << ")" << std::endl;


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




   const char *Path::find_latest(std::string filename)
   {
      get_instance();

      std::string path_to_return = "";
      size_t n = std::count(filename.begin(), filename.end(), '#');
      std::size_t pos_of_2_pounds = filename.find("##");
      if (n != 2 || pos_of_2_pounds == std::string::npos)
      {
         std::cout << "Path::find_latest(\"" << filename << "\") does not contain 2 ajacent # signs (##)" << std::endl;
         std::cout << "\tswitching to Path::find(\"" << filename << "\")" << std::endl;
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




   Path::~Path()
   {
      for (unsigned i=0; i<path.size(); i++)
         al_destroy_path(path[i]);
   }




   void Path::str_out()
   {
      get_instance();

      for (unsigned i=0; i<path.size(); i++)
      {
         std::cout << al_path_cstr(path[i], ALLEGRO_NATIVE_PATH_SEP) << std::endl;
      }
   }




   void Path::rescan()
   {
      get_instance();

      // clean out the previous
      for (unsigned i=0; i<path.size(); i++)
         al_destroy_path(path[i]);

      // repopulate
      ALLEGRO_FS_ENTRY *folder = al_create_fs_entry(".");
      _recursive_traverse_dir(folder);
      std::sort(path.begin(), path.end(), path_filename_comp);
      al_destroy_fs_entry(folder);
   }




   Path *Path::instance = NULL;
   std::vector<ALLEGRO_PATH *> Path::path;
}



