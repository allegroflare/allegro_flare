


#include <allegro_flare/attr_save_load.h>
#include <allegro_flare/useful.h>
//#include <sstream>
#include <allegro_flare/useful_php.h>




class Attr
{
public:
	std::string identifier;
	void *val;
	bool (*populate_func)(void *val, std::string str);
	std::string (*get_str_func)(void *val);
	Attr(std::string identifier, void *val, bool (*populate_func)(void *val, std::string str), std::string (*get_str_func)(void *val))
		: identifier(identifier)
		, val(val)
		, populate_func(populate_func)
		, get_str_func(get_str_func)
	{}
	bool set(std::string str)
	{
		if (populate_func) return populate_func(val, str);
		return false;
	}
	std::string get_str()
	{
		if (get_str_func) return get_str_func(val);
		return "";
	}
};





static bool populate_float(void *val, std::string str)
{
	float *cast_val = static_cast<float *>(val);

	*cast_val = atof(str.c_str());
	return true;
}

static std::string get_as_float(void *val)
{
	return tostring(*static_cast<float *>(val));
}




static bool populate_int(void *val, std::string str)
{
	int *cast_val = static_cast<int *>(val);

	*cast_val = atoi(str.c_str());
	return true;
}

static std::string get_as_int(void *val)
{
	return tostring(*static_cast<int *>(val));
}




static bool populate_bool(void *val, std::string str)
{
	float *cast_val = static_cast<float *>(val);

	if (str == "true") { *cast_val = true; return true; }
	if (str == "false") { *cast_val = false; return true; }
	return false;
}

static std::string get_as_bool(void *val)
{
	bool thing = *static_cast<bool *>(val);
	if (thing) return "true";
	else return "false";
}




static bool populate_string(void *val, std::string str)
{
	std::string *cast_val = static_cast<std::string *>(val);
	*cast_val = str;
	return true;
}

static std::string get_as_string(void *val)
{
	std::string thing = *static_cast<std::string *>(val);
	return thing;
}




static bool populate_ALLEGRO_COLOR(void *val, std::string str)
{
	ALLEGRO_COLOR *cast_val = static_cast<ALLEGRO_COLOR *>(val);

	// format "r g b a";
	std::vector<std::string> tokens = php::explode(" ", str);
	if (tokens.size() != 4) return false;
	cast_val->r = atof(tokens[0].c_str());
	cast_val->g = atof(tokens[1].c_str());
	cast_val->b = atof(tokens[2].c_str());
	cast_val->a = atof(tokens[3].c_str());
	return true;
}

static std::string get_as_ALLEGRO_COLOR(void *val)
{
	ALLEGRO_COLOR *cast_val = static_cast<ALLEGRO_COLOR *>(val);

	std::stringstream ss;
	ss << cast_val->r << " " << cast_val->g << " " << cast_val->b << " " << cast_val->a;
	return ss.str();
}











AttrLoader::AttrLoader() {}



AttrLoader::~AttrLoader()
{
	for (unsigned i=0; i<attr.size(); i++)
		delete attr[i];
	attr.clear();
}



void AttrLoader::register_var(std::string identifier, float *val)
{
	attr.push_back(new Attr(identifier, val, populate_float, get_as_float));
	sort_attrs();
}



void AttrLoader::register_var(std::string identifier, int *val)
{
	attr.push_back(new Attr(identifier, val, populate_int, get_as_int));
	sort_attrs();
}



void AttrLoader::register_var(std::string identifier, ALLEGRO_COLOR *val)
{
	attr.push_back(new Attr(identifier, val, populate_ALLEGRO_COLOR, get_as_ALLEGRO_COLOR));
	sort_attrs();
}



void AttrLoader::register_var(std::string identifier, bool *val)
{
	attr.push_back(new Attr(identifier, val, populate_bool, get_as_bool));
	sort_attrs();
}



void AttrLoader::register_var(std::string identifier, std::string *val)
{
	attr.push_back(new Attr(identifier, val, populate_string, get_as_string));
	sort_attrs();
}



void AttrLoader::register_var(std::string identifier, void *val, bool (*to_val_func)(void *val, std::string str), std::string (*to_str_func)(void *val))
{
	attr.push_back(new Attr(identifier, val, to_val_func, to_str_func));
	sort_attrs();
}




void AttrLoader::sort_attrs()
{
	std::sort(attr.begin(), attr.end());
	// TODO: make the list unique
}



Attr *AttrLoader::find_attr_record(std::string identifier)
{
	// TODO: make this a binary search
	for (unsigned i=0; i<attr.size(); i++)
	{
		if (attr[i]->identifier == identifier) return attr[i];
	}
	return NULL;
}



void AttrLoader::save_attrs(std::string filename, int num_tabs)
{
	std::ofstream outfile(filename.c_str());

	for (unsigned i=0; i<attr.size(); i++)
	{
		for (int t=0; t<num_tabs; t++) std::cout << "\t";
		outfile << attr[i]->identifier << "=" << attr[i]->get_str() << std::endl;
	}

	outfile.close();
}



void AttrLoader::load_attrs(std::string filename)
{
	std::ifstream infile(filename.c_str());
	if (!infile)
	{
		std::cout << "file not found." << std::endl;
		return;
	}

	Attr *found_attr = NULL;
	char buffer[256];
	std::string string_cheat;
	while (infile.getline(buffer, 256))
	{
		found_attr = NULL;
		string_cheat = buffer;
		string_cheat = php::trim(string_cheat);

		// find the pos of the '=' char
		size_t pos = string_cheat.find_first_of('='); 

		if (pos != std::string::npos)
		{
			std::string identifier = string_cheat.substr(0, pos);
			std::string value_str = string_cheat.substr(pos+1);
			found_attr = find_attr_record(identifier);
			if (found_attr) found_attr->set(value_str);
		}
	}

	infile.close();
}

