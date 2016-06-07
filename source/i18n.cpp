



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
   , current_language_name("")
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




std::string I18n::find_language_file(std::string locale)
{
   if (locale.empty()) return "";

   std::vector<std::string> filenames = get_instance()->get_language_filenames();

   for (auto &filename : filenames)
   {
      if (strncmp(locale.c_str(), filename.c_str(), locale.size()) == 0)
         return get_instance()->languages_folder + filename;
   }

   return "";
}




bool I18n::set_locale(std::string locale)
{
   std::string filename = find_language_file(locale);
   if (filename == "")
   {
      std::cout << CONSOLE_COLOR_RED;
      std::cout << "Could not find language file for locale \"" << locale << "\"";
      std::cout << CONSOLE_COLOR_DEFAULT;
      std::cout << std::endl;
      return false;
   }

   if (!load_language_file(locale, locale, filename)) return false;

   get_instance()->current_locale = locale;
   get_instance()->current_language_filename = filename;
   return true;
}




std::string I18n::get_locale()
{
   return get_instance()->current_locale;
}




bool I18n::load_language_file(std::string as_locale, std::string as_language_name, std::string filename)
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
      get_instance()->lines.clear();
      ALLEGRO_CONFIG_ENTRY *iterator = NULL;
      const char *key = al_get_first_config_entry(config_file, NULL, &iterator);
      while (iterator)
      {
         get_instance()->lines[key] = al_get_config_value(config_file, NULL, key);
         key = al_get_next_config_entry(&iterator);
      }

      al_destroy_config(config_file);

      get_instance()->current_locale = as_locale;
      get_instance()->current_language_name = as_language_name;
      get_instance()->current_language_filename = filename;
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




std::string I18n::get_language_name()
{
   return get_instance()->current_language_name;
}




bool I18n::t_exists(std::string label)
{
   return get_instance()->lines.find(label) != get_instance()->lines.end();
}




std::string I18n::t(std::string text_label)
{
   return get_instance()->lines[text_label];
}




std::string I18n::tf(std::string text_label, ...)
{
   std::string format = get_instance()->lines[text_label];
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




