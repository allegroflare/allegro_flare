


#include <AllegroFlare/Config.hpp>

#include <iostream>
#include <sstream>


namespace AllegroFlare
{
   Config::Config(std::string filename)
      : filename(filename)
      , config_file(nullptr)
   {
   }



   void Config::ensure_initialized_allegro()
   {
      if (!al_is_system_installed()) throw std::runtime_error("[Config]: attempting to use AllegroFlare/Config but allegro is not initialized.  You must call al_init() before using any of the AllegroFlare/Config functions.");
   }



   bool Config::load()
   {
      ensure_initialized_allegro();

      if (config_file) al_destroy_config(config_file);
      config_file = al_load_config_file(filename.c_str());

      if (!config_file)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::Config::" << __FUNCTION__ << "] the file \"" << filename << "\" could not be found." << std::endl;
         throw std::runtime_error(error_message.str());
      }
      return true;
   }




   bool Config::has_value(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return false;
      return true;
   }




   std::string Config::get_value_str(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return "";
      return val;
   }




   int Config::get_value_int(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return 0;
      return atoi(val);
   }




   float Config::get_value_float(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return 0;
      return atof(val);
   }



   bool Config::get_value_bool(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return false;
      return std::string(val) == BOOL_STRING_FOR_TRUE;
   }



   std::string Config::get_or_default_str(std::string section, std::string key, std::string _default)
   {
      ensure_initialized_allegro();
      if (has_value(section, key)) return get_value_str(section, key);
      return _default;
   }




   int Config::get_or_default_int(std::string section, std::string key, int _default)
   {
      ensure_initialized_allegro();
      if (has_value(section, key)) return get_value_int(section, key);
      return _default;
   }




   float Config::get_or_default_float(std::string section, std::string key, float _default)
   {
      ensure_initialized_allegro();
      if (has_value(section, key)) return get_value_float(section, key);
      return _default;
   }



   bool Config::get_or_default_bool(std::string section, std::string key, bool _default)
   {
      ensure_initialized_allegro();
      if (has_value(section, key)) return get_value_bool(section, key);
      return _default;
   }



   const std::string Config::BOOL_STRING_FOR_TRUE = "true";
}



