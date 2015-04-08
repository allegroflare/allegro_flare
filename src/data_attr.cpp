





#include <allegro_flare/data_attr.h>




//std::vector<DataAttr *> DataAttr::data_attr_elements;




DataAttr::DataAttr()
	: data()
{
	//data_attr_elements.push_back(this);
}




bool DataAttr::has(std::string key)
{
	return (data.find(key) != data.end());
}



bool DataAttr::remove(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return false;
	data.erase(it);
}



bool DataAttr::matches(std::string key, std::string value)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return false;
	return (it->second == value);
}




std::string DataAttr::get(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return "";
	return it->second;
}




int DataAttr::get_as_int(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return 0;
	return atoi(it->second.c_str());
}




float DataAttr::get_as_float(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return 0;
	return (float)atof(it->second.c_str());
}




std::string DataAttr::get_as_string(std::string key)
{
	return get(key);
}



#include <allegro_flare/useful_php.h>

bool DataAttr::get_as_bool(std::string key)
{
	std::map<std::string, std::string>::iterator it=data.find(key);
	if (it == data.end()) return 0;
	std::string trimmed = php::trim(it->second);
	if (php::strtoupper(trimmed) == "FALSE") return false;
	if (trimmed == "0") return false;

	if (trimmed == "1") return true;
	if (php::strtoupper(trimmed) == "TRUE") return true;

	return true; // eh... ok, screw it. :/
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
	//for (unsigned i=0; i<data_attr_elements.size(); i++)
	//{
	//	if (this == data_attr_elements[i])
	//		data_attr_elements.erase(data_attr_elements.begin() + i);
	//}
}



/*
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
*/



bool DataAttr::load(std::string filename)
	// TODO: this function needs options, maybe as a second flags parameter, for example:
	// - keep existing keys/values and overwrite if there is a match
	// - clear existing keys/values and load the file
	// - output errors
	// - load a different format, for example:
	//   - key_one="hello ther" key_two="this is another" // inline HTML attributes
	//   - key_one=3539 key_two="sdjfio a" key_three=Hunky // a dirty format
	//   - (key1, key2, key3, key4) (val1, "val2", TRUE, "val\", 4" // SQL
	//   - color: #928491; // CSS style
	//   - key_name = key_val // this is the current format that is loaded, each key/value on a line
	// TODO: make the second parameter a string to parse, not a file to load and parse
{
	int num_key_vals_successfuly_loaded = 0;

	if (!php::file_exists(filename))
	{
		std::cout << "[DataAttr:load] error, cannot find file \"" << filename << "\"" << std::endl;
		return false;
	}

	data.clear();

	std::vector<std::string> lines = php::explode("\n", php::file_get_contents(filename));
	for (unsigned i=0; i<lines.size(); i++)
	{
		size_t pos_of_comments_token = lines[i].find_first_of("//");
		if (pos_of_comments_token != std::string::npos)
		{
			// there is a comment token, remove it and the trailing characters from this line
			lines[i] = lines[i].substr(0, pos_of_comments_token);
		}


		// if the line is empty, move to the next line

		if (php::trim(lines[i]) == "") continue;


		// now, look for the delimiter

		size_t pos_of_first_equals_sign = lines[i].find_first_of('=');
		if (pos_of_first_equals_sign == std::string::npos)
		{
			// error, no '=' delimiter found
		}
		else
		{
			std::string key = lines[i].substr(0, pos_of_first_equals_sign);
			std::string value = lines[i].substr(pos_of_first_equals_sign+1);
			key = php::trim(key);
			value = php::trim(value);
			
			set(key, value);

			num_key_vals_successfuly_loaded++;
		}
	}

	std::cout << "\"" << filename << "\" parsed. " << num_key_vals_successfuly_loaded << " val(s) loaded." << std::endl;

	return true;
}




bool DataAttr::save(std::string filename)
{
	std::stringstream output;

	for (std::map<std::string, std::string>::iterator it=data.begin(); it != data.end(); it++)
	{
		output << it->first << " = " << it->second << std::endl;
	}

	return php::file_put_contents(filename, output.str());
}




unsigned DataAttr::size()
{
	return data.size();
}



std::map<std::string, std::string> DataAttr::get_copy()
{
	return data;
}
