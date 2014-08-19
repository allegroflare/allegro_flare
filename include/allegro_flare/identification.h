#ifndef __AF_IDENTIFICATION_HEADER
#define __AF_IDENTIFICATION_HEADER




#include <algorithm>
#include <sstream>
#include <vector>

class ElementIDManager;

class ElementID
{
private:
	ElementIDManager *manager;
	static int next_unique_id_num;
	int unique_id_num;
	std::string id;
	std::vector<std::string> classes;
	friend class ElementIDManager;

public:
	void add_class(std::string _class);
	void remove_class(std::string _class);
	bool has_class(std::string _class);
	std::vector<std::string> get_classes() { return classes; }

	void set_id(std::string id);
	std::string get_id() { return id; }
	std::string get_id_info_str();
	ElementID(ElementIDManager *manager);
	~ElementID();
};


class ElementIDManager
{
private:
	//ElementIDManager *instance;
	friend class ElementID;
	void add(ElementID *obj);
	void remove(ElementID *obj);
//	ElementID *selected;

public:

	ElementIDManager();
	std::vector<ElementID *> object; // private for the most part, but accessible for usefulness
	//ElementIDManager *get_instance();
	ElementID *get_element_by_id(std::string id);
	std::vector<ElementID *> get_elements_by_class(std::string class_name); // <- todo
};










#endif