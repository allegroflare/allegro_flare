


#include <AllegroFlare/Config.hpp>

#include <iostream>




namespace AllegroFlare
{
   Config::Config(std::string filename)
      : filename(filename)
      , config_file(nullptr)
   {
   }



   bool Config::load()
   {
      if (!config_file)
      {
         std::cerr << "[" << __FUNCTION__ << "] the file \"" << filename << "\" could not be found." << std::endl;
         return false;
      }
      return true;
   }




   bool Config::has_value(std::string section, std::string key)
   {
      if (!config_file) return false;
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return false;
      return true;
   }




   std::string Config::get_value_str(std::string section, std::string key)
   {
      if (!config_file) return "";
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return "";
      return val;
   }




   int Config::get_value_int(std::string section, std::string key)
   {
      if (!config_file) return 0;
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return 0;
      return atoi(val);
   }




   float Config::get_value_float(std::string section, std::string key)
   {
      if (!config_file) return 0;
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return 0;
      return atof(val);
   }




   std::string Config::get_or_default_str(std::string section, std::string key, std::string _default)
   {
      if (has_value(section, key)) return get_value_str(section, key);
      return _default;
   }




   int Config::get_or_default_int(std::string section, std::string key, int _default)
   {
      if (has_value(section, key)) return get_value_int(section, key);
      return _default;
   }




   float Config::get_or_default_float(std::string section, std::string key, float _default)
   {
      if (has_value(section, key)) return get_value_float(section, key);
      return _default;
   }
}



