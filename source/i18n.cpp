



#include <allegro_flare/i18n.h>

#include <allegro5/allegro.h>

#include <allegro_flare/console_color.h>

#include <iostream>



I18n *I18n::instance = nullptr;




I18n *I18n::get_instance()
{
   if (instance == nullptr) instance = new I18n();
   return instance;
}




I18n::I18n()
   : languages_folder("")
   , current_locale("")
   , current_language_filename("")
   , lines()
{}




I18n::~I18n()
{
}




bool I18n::initialize(std::string folder)
{
   get_instance();
   return set_languages_folder(folder);
}




bool I18n::destruct()
{
   if (instance)
   {
      delete instance;
      instance = nullptr;
      return true;
   }
   return false;
}




bool I18n::set_languages_folder(std::string folder)
{
   if (!al_filename_exists(folder.c_str()))
   {
      std::cout << CONSOLE_COLOR_RED;
      std::cout << "Could not open folder \"" << folder << "\" to find language files.";
      std::cout << CONSOLE_COLOR_DEFAULT;
      std::cout << std::endl;
      return false;
   }
   get_instance()->languages_folder = folder;
   return true;
}




std::string I18n::get_languages_folder()
{
   return get_instance()->languages_folder;
}




bool I18n::set_locale(std::string locale)
{
   return false;
}




bool I18n::load_language_file(std::string filename)
{
   return false;
}




std::string I18n::get_locale()
{
   return "";
}




std::string I18n::get_language_name()
{
   return "";
}




std::string I18n::t(std::string text_label)
{
   return "";
}




std::vector<std::string> I18n::get_language_filenames()
{
   std::vector<std::string> results;
   ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(get_instance()->languages_folder.c_str());
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




