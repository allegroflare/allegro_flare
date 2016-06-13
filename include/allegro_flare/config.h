#ifndef __AF_CONFIG_HEADER
#define __AF_CONFIG_HEADER




#include <string>
#include <allegro5/allegro.h>




class Config
{
public:
   std::string filename;
   ALLEGRO_CONFIG *config_file;

   Config(std::string filename);

   bool has_value(std::string section, std::string key);
   std::string get_value_str(std::string section, std::string key);
   int get_value_int(std::string section, std::string key);
   float get_value_float(std::string section, std::string key);

   std::string get_or_default_str(std::string section, std::string key, std::string _default);
   int get_or_default_int(std::string section, std::string key, int _default);
   float get_or_default_float(std::string section, std::string key, float _default);
};




#endif
