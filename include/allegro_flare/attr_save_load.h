#ifndef __AF_ATTR_SAVE_LOAD_HEADER
#define __AF_ATTR_SAVE_LOAD_HEADER




/*{

= title =
AttrLoader

= description =
AttrLoader is a useful tool for easily saving and loading values to and from an object.
To use it, you register the object's variables (and identifiers) inside your object's constructor with the register_var(*) function.
Then, saving and loading is as simple as calling save_attrs() and load_attrs()

}*/



#include <string>
#include <vector>

#include <allegro5/allegro_color.h>



class Attr;


class AttrLoader
{
private:
	// managing
	void sort_attrs();
	Attr *find_attr_record(std::string identifier);
	std::vector<Attr *> attr;

public:

	AttrLoader();
	~AttrLoader();


	// register attributes and variables

	void register_var(std::string identifier, float *val);
	void register_var(std::string identifier, int *val);
	void register_var(std::string identifier, ALLEGRO_COLOR *val);
	void register_var(std::string identifier, bool *val);
	void register_var(std::string identifier, std::string *val);
	void register_var(std::string identifier, void *val, bool (*to_val_func)(void *val, std::string str), std::string (*to_str_func)(void *val));

	// saving and loading

	void save_attrs(std::string filename, int num_tabs=0);
	void load_attrs(std::string filename);
};





#endif