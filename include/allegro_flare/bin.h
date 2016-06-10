#ifndef __AF_BIN_TEMPLATE
#define __AF_BIN_TEMPLATE




#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro_flare/console_color.h>
#include <allegro_flare/useful.h>
#include <allegro_flare/useful_php.h>




template <class T>
class Bin
{
public:
	class Record
	{
	public:
		std::string identifier;
		ALLEGRO_PATH *file_path;
		T data;

		Record(std::string identifier, ALLEGRO_PATH *file_path, T data);
		~Record();
	};

	Bin(std::string directory);
	void __check_al_system_is_installed();
	void set_path(std::string directory); // <- hmm
	void set_full_path(std::string directory); // <- hmm
	virtual ~Bin(); // < should this be a pure virtual funcion that requires clear()?
	Record *get_record(std::string identifier);
	T get(std::string identifier);
	T auto_get(std::string identifier);
	bool load(std::string identifier, std::string filename);
	bool include(std::string identifier, T data);
	bool rename(std::string identifier, std::string new_identifer);
	void clear(); //< doesn't work as a base class function in the destructor
	virtual T load_data(std::string identifier) = 0;
	virtual void destroy_data(T) = 0;
	std::string get_str();
	T operator[](const std::string &identifier); // this is equivelent to auto_get()

	// TODO: virtual T clone(std::string existing_identifier, std::string new_clone_identifier);

private:
	ALLEGRO_PATH *directory;
	std::vector<Record *> record;
};




template<class T>
static bool bin_record_comp(const typename Bin<T>::Record *b1, const typename Bin<T>::Record *b2)
{
	return b1->identifier.compare(b2->identifier) < 0;
}




template<class T>
Bin<T>::Bin(std::string dir)
   : directory(NULL)
   , record()
{
   set_path(dir);
   if (!al_is_system_installed())
      std::cout << "DEPRECIATION ERROR: Bins can no longer be created prior to al_init(). You have probably tried to create a bin in the global namespace." << std::endl;
}




template<class T>
Bin<T>::~Bin()
{}




template<class T>
Bin<T>::Record::Record(std::string identifier, ALLEGRO_PATH *file_path, T data)
	: identifier(identifier)
	, file_path(file_path)
	, data(data)
{
	//std::cout << "Bin::Record created -> " << identifier << std::endl;
}




template<class T>
Bin<T>::Record::~Record()
{
	if (file_path) al_destroy_path(file_path);
	// destroy T?
}




template<class T>
void Bin<T>::set_path(std::string path)
{
	std::vector<std::string> path_parts = php::explode("/", path);
	if (directory) al_destroy_path(directory);
	directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	for (std::vector<std::string>::iterator it=path_parts.begin(); it!=path_parts.end(); it++)
	{
		al_append_path_component(directory, it->c_str());
	}
}




template<class T>
void Bin<T>::set_full_path(std::string path)
{
	if (directory) al_destroy_path(directory);
	directory = al_create_path_for_directory(path.c_str());
}




template<class T>
typename Bin<T>::Record *Bin<T>::get_record(std::string identifier)
{
	int first, last, mid, comp;

	if (record.empty()) return NULL;

	first = 0;
	last = record.size()-1;

	while (first <= last)
	{
		mid = (first + last) / 2;  // compute mid point.
		comp = record[mid]->identifier.compare(identifier);

		if (comp < 0) first = mid + 1;  // repeat search in top half.
		else if (comp > 0) last = mid - 1; // repeat search in bottom half.
		else return record.at(mid);     // found it. return position
	}

	return NULL;
}




template<class T>
T Bin<T>::get(std::string identifier)
{
	Bin<T>::Record *r = get_record(identifier);
	if (r) return r->data;
	std::cout << CONSOLE_COLOR_RED << "[" << __FUNCTION__ << "] could not load \"" << identifier << "\"" << CONSOLE_COLOR_DEFAULT << std::endl;
	return NULL;
}




template<class T>
T Bin<T>::auto_get(std::string identifier)
{
	Bin<T>::Record *r = get_record(identifier);
	if (r) return r->data;

	if (load(identifier, identifier))
	{
		std::cout << CONSOLE_COLOR_YELLOW << "["  << __FUNCTION__  << "] Record \"" << identifier << "\" auto-created" << CONSOLE_COLOR_DEFAULT << std::endl;
		return get(identifier);
	}

	std::cout << CONSOLE_COLOR_RED << "["  << __FUNCTION__  << "] could not load \"" << identifier << "\"" << CONSOLE_COLOR_DEFAULT << std::endl;
	return NULL;
}




template<class T>
bool Bin<T>::load(std::string identifier, std::string filename)
{
	ALLEGRO_PATH *path = NULL;
	Bin<T>::Record *r = get_record(identifier);
	if (r) return false;

	if (directory)
	{
		path = al_clone_path(directory);
		al_set_path_filename(path, filename.c_str()); //<- should probably be append_path_thing
	}

	r = new Bin<T>::Record(identifier, path, load_data(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP)));
	//r->identifier = identifier;
	//r->file_path = path;
	//std::cout << "4";
	//r->data = load_data(al_path_cstr(r->file_path, ALLEGRO_NATIVE_PATH_SEP));

	//std::cout << "4";

	record.push_back(r);
	std::sort(record.begin(), record.end(), bin_record_comp<T>);

	if (!r->data) return false;
	return true;
}




template<class T>
bool Bin<T>::include(std::string identifier, T data)
{
	// check if the record already exists
	Bin<T>::Record *r = get_record(identifier);
	if (r) return false;

	// create a new record
	r = new Bin<T>::Record(identifier, NULL, data);
	record.push_back(r);

	// sort
	std::sort(record.begin(), record.end(), bin_record_comp<T>);

	// return success or failure
	if (!r->data) return false;
	return true;
}




template<class T>
bool Bin<T>::rename(std::string identifier, std::string new_identifer)
	// be sure to test this
{
	Bin<T>::Record *r = get_record(identifier);
	if (!r) return false;

	r->identifier = new_identifer;

	std::sort(record.begin(), record.end(), bin_record_comp<T>);

	return true;
}




template<class T>
void Bin<T>::clear()
{
	// hmm... this function doesn't work if you place it in this base class's destructor
	// the derived class is destructed before this base class.  destroy_data is a pure virtual function
	// from the derived class.
	for (typename std::vector<Bin<T>::Record *>::iterator it=record.begin(); it!=record.end(); it++)
	{
		destroy_data((*it)->data);
		delete (*it);
	}
	//record.clear();
	record.clear();
}




template<class T>
std::string Bin<T>::get_str()
{
	std::stringstream result;
	result << "Bin dump" << std::endl;
	for (unsigned i=0; i<record.size(); i++)
		result << i << ": " << record[i]->identifier;
	return result.str();
}




template<class T>
T Bin<T>::operator[](const std::string &identifier)
{
	return auto_get(identifier);
}




#endif
