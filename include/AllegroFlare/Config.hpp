#pragma once


#include <string>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Config
   {
   private:
      static const std::string BOOL_STRING_FOR_TRUE;
      std::string filename;
      ALLEGRO_CONFIG *config_file;
      void ensure_initialized_allegro();

   public:
      Config(std::string filename);

      bool load();

      bool has_value(std::string section, std::string key);
      std::string get_value_str(std::string section, std::string key);
      int get_value_int(std::string section, std::string key);
      float get_value_float(std::string section, std::string key);
      bool get_value_bool(std::string section, std::string key);

      std::string get_or_default_str(std::string section, std::string key, std::string _default);
      int get_or_default_int(std::string section, std::string key, int _default);
      float get_or_default_float(std::string section, std::string key, float _default);
      bool get_or_default_bool(std::string section, std::string key, bool _default);
   };
}


