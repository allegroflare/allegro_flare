



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




