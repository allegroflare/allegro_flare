


#include <allegro_flare/config.h>

#include <iostream>




ConfigSettings::ConfigSettings(std::string filename)
	: filename(filename)
	, config_file(al_load_config_file(filename.c_str()))
{
	if (!config_file)
	{
		std::cerr << "[" << __FUNCTION__ << "] the file \"" << filename << "\" could not be found." << std::endl;
		return;
	}
}




bool ConfigSettings::has_value(std::string section, std::string key)
{
	if (!config_file) return false;
	const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
	if (!val) return false;
	return true;
}




std::string ConfigSettings::get_value_str(std::string section, std::string key)
{
	if (!config_file) return "";
	const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
	if (!val) return "";
	return val;
}




int ConfigSettings::get_value_int(std::string section, std::string key)
{
	if (!config_file) return 0;
	const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
	if (!val) return 0;
	return atoi(val);
}




float ConfigSettings::get_value_float(std::string section, std::string key)
{
	if (!config_file) return 0;
	const char *val = al_get_config_value(config_file, section.c_str(), key.c_str());
	if (!val) return 0;
	return atof(val);
}




