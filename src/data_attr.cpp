





#include <allegro_flare/data_attr.h>




std::vector<DataAttr *> DataAttr::data_attr_elements;





DataAttr::DataAttr()
{
	data_attr_elements.push_back(this);
}




bool DataAttr::has(std::string key)
{
	return (data.find(key) != data.end());
}




std::string DataAttr::get(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return "";
	return it->second;
}




bool DataAttr::set(std::string key, std::string value)
	// returns true if the key was found.
	// returns false if a new key was created.
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end())
	{
		// create a new one
		data[key] = value;
		return false;
	}
	it->second = value;
	return true;
}




DataAttr::~DataAttr()
{
	for (unsigned i=0; i<data_attr_elements.size(); i++)
	{
		if (this == data_attr_elements[i])
			data_attr_elements.erase(data_attr_elements.begin() + i);
	}
}




DataAttr *DataAttr::get_element_by_id(std::string id)
{
	//std::cout << "searching for element with id \"" << id << "\"...";
	for (unsigned i=0; i<data_attr_elements.size(); i++)
	{
		std::map<std::string, std::string>::iterator it = data_attr_elements[i]->data.find("id");
		if (it == data_attr_elements[i]->data.end()) continue;

		if ((*it).second == id)
		{
			//std::cout << "found." << std::endl;
			return data_attr_elements[i];
		}
	}
	//std::cout << "could not be found." << std::endl;
	return NULL;
}


