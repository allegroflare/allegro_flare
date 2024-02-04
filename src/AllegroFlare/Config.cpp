


#include <AllegroFlare/Config.hpp>

#include <iostream>
#include <sstream>
#include <AllegroFlare/Errors.hpp>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
   Config::Config(std::string filename)
      : filename(filename)
      , config_file(nullptr)
      , initialized(false)
   {
   }



   void Config::ensure_initialized_allegro()
   {
      if (!al_is_system_installed()) throw std::runtime_error("[Config]: attempting to use AllegroFlare/Config but allegro is not initialized.  You must call al_init() before using any of the AllegroFlare/Config functions.");
   }


   void Config::ensure_not_initialized()
   {
      if (initialized) throw std::runtime_error("[Config::ensure_initialized()]: Not initialized.");
   }


   void Config::set_filename(std::string filename)
   {
      ensure_not_initialized();
      this->filename = filename;
   }


   std::string Config::get_filename()
   {
      return filename;
   }


   bool Config::load_or_create_empty(bool output_warning_if_auto_created)
   {
      ensure_initialized_allegro();

      if (config_file) al_destroy_config(config_file);
      config_file = al_load_config_file(filename.c_str());

      if (!config_file)
      {
         if (output_warning_if_auto_created)
         {
            std::stringstream error_message;

            // TODO: Remove this warning from AllegroFlare/Config, and move it to the caller(s), (probably 
            // AllegroFlare/Frameworks/Full if not in other places).  Also, refactor this AllegroFlare/Config a bit
            // and add a "will_config_be_auto_created()" that would be called (and potentially emit the warning) before
            // calling this "load_or_create_empty" function.
            error_message << "A config file \""
                          << filename
                          << "\" was not found so a config will be created automatically. To stop this warning, "
                          << "you create the config file, or disable this warning entirely with "
                          << "\"AllegroFlare::Frameworks::Full::disable_auto_created_config_warning()\".";

            std::stringstream from;
            from << "AllegroFlare::Config::" << __func__;

            AllegroFlare::Errors::warn_from(from.str(), error_message.str());
         }

         config_file = al_create_config();

         if (output_warning_if_auto_created)
         {
            //std::cerr << " Done: empty config created." << std::endl;
         }
      }

      initialized = true;

      return true;
   }



   bool Config::load()
   {
      // TODO: fix guard against duplicate initialization
      ensure_initialized_allegro();

      if (config_file) al_destroy_config(config_file);
      config_file = al_load_config_file(filename.c_str());

      if (!config_file)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::Config::" << __FUNCTION__ << "] the file \"" << filename << "\" could not be found." << std::endl;
         throw std::runtime_error(error_message.str());
      }

      initialized = true;

      return true;
   }



   bool Config::reload()
   {
      // TODO: Fix guard against duplicate initialization
      // TODO: Permit reloading to work even in the case of double initialization
      return load();
   }



   bool Config::has_value(std::string section, std::string key)
   {
      ensure_initialized_allegro();
      const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
      if (!val) return false;
      return true;
   }



   bool Config::has_section(std::string section)
   {
      // NOTE: Look over dangling pointer concern with the way iterator is handled by allegro
      ALLEGRO_CONFIG_SECTION* iterator = nullptr;

      ensure_initialized_allegro();
      const char *val = al_get_first_config_section(config_file, &iterator);
      if (!val) return false;

      do {
         std::string val_as_string(val);
         if (val_as_string == section) return true;
      } while ((val = al_get_next_config_section(&iterator)));

      return false;
   }



   std::vector<std::string> Config::get_section_keys(std::string section)
   {
      std::vector<std::string> result;

      // NOTE: Look over dangling pointer concern with the way iterator is handled by allegro
      ALLEGRO_CONFIG_ENTRY* iterator = nullptr;

      ensure_initialized_allegro();
      const char *val = al_get_first_config_entry(config_file, section.c_str(), &iterator);
      if (!val)
      {
         AllegroFlare::Errors::throw_error(
            "AllegroFlare::Config::get_section_keys",
            "The section \"" + section + "\" does not exist."
         );
      }
      result.push_back(std::string(val));

      while ((val = al_get_next_config_entry(&iterator)))
      {
         result.push_back(std::string(val));
      }

      return result;
   }




   std::string Config::get_value_str(std::string section, std::string key)
   {
      AllegroFlare::Errors::warn_from_once(
         "AllegroFlare::Config::get_value_str",
         "\"get_value_str\" is depreciated, please use \"get_value_string\"."
      );

      return get_value_string(section, key);
   }



   std::string Config::get_value_string(std::string section, std::string key)
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



