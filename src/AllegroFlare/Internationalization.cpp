



#include <AllegroFlare/Internationalization.hpp>

#include <iostream>
#include <allegro5/allegro.h>
#include <AllegroFlare/ConsoleColor.hpp>




namespace AllegroFlare
{
   Internationalization::Internationalization(std::string languages_folder)
      : languages_folder(languages_folder)
      , current_language_code("")
      , current_language_name("")
      , current_language_filename("")
      , lines()
   {}




   Internationalization::~Internationalization()
   {
   }




   bool Internationalization::set_languages_folder(std::string folder)
   {
      if (!al_filename_exists(folder.c_str()))
      {
         std::cout << CONSOLE_COLOR_RED
                   << "[AllegroFlare::Internationalization::set_languages_folder()]: error: Could not open folder "
                   << "\"" << folder << "\" to find language files."
                   << CONSOLE_COLOR_DEFAULT
                   << std::endl
                   ;
         return false;
      }
      languages_folder = folder;
      return true;
   }




   std::string Internationalization::get_languages_folder()
   {
      return languages_folder;
   }




   std::string Internationalization::find_language_file(std::string language_code)
   {
      if (language_code.empty()) return "";

      std::vector<std::string> filenames = get_language_filenames();

      for (auto &filename : filenames)
      {
         if (strncmp(language_code.c_str(), filename.c_str(), language_code.size()) == 0)
            return languages_folder + filename;
      }

      return "";
   }




   bool Internationalization::set_language(std::string language_code)
   {
      std::string filename = find_language_file(language_code);
      if (filename == "")
      {
         std::cout << CONSOLE_COLOR_RED
                   << "[AllegroFlare::Internationalization::set_language()]: error: "
                   << "Could not find language file for language_code \"" << language_code << "\""
                   << CONSOLE_COLOR_DEFAULT
                   << std::endl
                   ;
         return false;
      }

      if (!load_language_file(language_code, language_code, filename)) return false;

      current_language_code = language_code;
      current_language_filename = filename;
      return true;
   }




   std::string Internationalization::get_language()
   {
      return current_language_code;
   }




   bool Internationalization::load_language_file(std::string as_language_code, std::string as_language_name, std::string filename)
   {
      if (!al_filename_exists(filename.c_str()))
      {
         std::cout << CONSOLE_COLOR_RED;
         std::cout << "Cannot load language file \"" << filename << "\"";
         std::cout << CONSOLE_COLOR_DEFAULT;
         std::cout << std::endl;
         return false;
      }

      ALLEGRO_CONFIG *config_file = al_load_config_file(filename.c_str());
      if (config_file)
      {
         lines.clear();
         ALLEGRO_CONFIG_ENTRY *iterator = NULL;
         const char *key = al_get_first_config_entry(config_file, NULL, &iterator);
         while (iterator)
         {
            lines[key] = al_get_config_value(config_file, NULL, key);
            key = al_get_next_config_entry(&iterator);
         }

         al_destroy_config(config_file);

         current_language_code = as_language_code;
         current_language_name = as_language_name;
         current_language_filename = filename;
      }
      else
      {
         std::cout << CONSOLE_COLOR_RED;
         std::cout << "Malformed language file \"" << filename << "\".  See ALLEGRO_CONFIG docs for proper format.";
         std::cout << CONSOLE_COLOR_DEFAULT;
         std::cout << std::endl;
         al_destroy_config(config_file);
         return false;
      }

      return true;
   }




   std::string Internationalization::get_language_name()
   {
      return current_language_name;
   }




   bool Internationalization::t_exists(std::string label)
   {
      return lines.find(label) != lines.end();
   }




   std::string Internationalization::t(std::string text_label)
   {
      return lines[text_label];
   }




   std::string Internationalization::tf(std::string text_label, ...)
   {
      std::string format = lines[text_label];
      char buff[512];

      va_list args;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"
      va_start(args, format);
#pragma clang diagnostic pop

      vsnprintf(buff, sizeof(buff), format.c_str(), args);
      va_end(args);

      return buff;
   }




   std::vector<std::string> Internationalization::get_language_filenames()
   {
      std::vector<std::string> results;
      ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(languages_folder.c_str());
      ALLEGRO_FS_ENTRY* entry = nullptr;
      ALLEGRO_PATH *path = nullptr;

      if (al_open_directory(dir))
      {
         while((entry = al_read_directory(dir)))
         {
            uint32_t flags = al_get_fs_entry_mode(entry);

            if (flags & ALLEGRO_FILEMODE_ISFILE)
            {
               path = al_create_path(al_get_fs_entry_name(entry));
               results.push_back(al_get_path_filename(path));
               al_destroy_path(path);
            }

            al_destroy_fs_entry(entry);
            entry = nullptr;
         }
      }
      else
      {
         std::cout << "something went wrong" << std::endl;
      }

      al_destroy_fs_entry(dir);

      return results;
   }
}



