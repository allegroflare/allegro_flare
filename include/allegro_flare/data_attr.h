#ifndef __ALLEGRO_FLARE_DATA_ATTR_HEADER
#define __ALLEGRO_FLARE_DATA_ATTR_HEADER






#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>


class DataAttr
{
private:
	static std::vector<DataAttr *> data_attr_elements;
		// a list of all the elements that have data attributes.
		// Assuming several elements might have an "id" attribute
		// then this list allows a person to search all of the
		// elements with an id, and return that element.

public:
	DataAttr();
	~DataAttr();

	std::map<std::string, std::string> data; // basically, use the map<>.
											 // this was just recently moved to private
	bool has(std::string key);
	std::string get(std::string key);
	bool set(std::string key, std::string value);

	static DataAttr *get_element_by_id(std::string id);
};







#endif