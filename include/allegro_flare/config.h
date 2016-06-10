#ifndef __AF_CONFIG_HEADER
#define __AF_CONFIG_HEADER




#include <string>
#include <allegro5/allegro.h>



class ConfigSettings
{
public:
	std::string filename;
	ALLEGRO_CONFIG *config_file;

	ConfigSettings(std::string filename);

	bool has_value(std::string section, std::string key);
	std::string get_value_str(std::string section, std::string key);
	int get_value_int(std::string section, std::string key);
	float get_value_float(std::string section, std::string key);
};




#endif
