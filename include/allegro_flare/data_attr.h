#ifndef __ALLEGRO_FLARE_DATA_ATTR_HEADER
#define __ALLEGRO_FLARE_DATA_ATTR_HEADER






#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>


class DataAttr
{
private: // maybe private?
	std::map<std::string, std::string> data;

public:
	DataAttr();
	~DataAttr();

	std::string get(std::string key);
	bool set(std::string key, std::string value);
	bool has(std::string key);
	bool matches(std::string key, std::string value); // checks if there is a matching key with value

	int get_as_int(std::string key);
	float get_as_float(std::string key);
	std::string get_as_string(std::string key);
	bool get_as_bool(std::string key);

	bool load(std::string filename);
	bool save(std::string filename);

	unsigned size();
	std::map<std::string, std::string> get_copy();
};







#endif