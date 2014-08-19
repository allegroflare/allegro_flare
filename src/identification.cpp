


#include <allegro_flare/identification.h>



//ElementIDManager *ElementIDManager::instance = NULL;
//ElementIDManager::ElementIDManager()
//	: selected(NULL)
//{};
//ElementIDManager *ElementIDManager::get_instance()
//{
//	if (!instance) instance = new ElementIDManager();
//	return instance;
//}
//std::vector<ElementID *> ElementIDManager::object;
//ElementID *ElementIDManager::selected = NULL;
void ElementIDManager::add(ElementID *obj) { object.push_back(obj); }
void ElementIDManager::remove(ElementID *obj)
{
	// (fix this, it's linear)
	for (unsigned i=0; i<object.size(); i++)
	{
		if (object[i] == obj)
		{
			object.erase(object.begin()+i);
			return;
		}
	}
}
ElementID *ElementIDManager::get_element_by_id(std::string id)
{
	// (fix this, it's linear)
	for (unsigned i=0; i<object.size(); i++)
	{
		if (object[i]->id == id) return object[i];
	}
	return NULL;
}


ElementID::ElementID(ElementIDManager *manager)
	: manager(manager)
	, unique_id_num(next_unique_id_num++)
{
	if (manager) manager->add(this);
}
ElementID::~ElementID() { if (manager) manager->remove(this); }
int ElementID::next_unique_id_num = 0;
void ElementID::set_id(std::string id) { this->id = id; }
void ElementID::add_class(std::string _class)
{
	if (!has_class(_class)) classes.push_back(_class);
}
void ElementID::remove_class(std::string _class)
{
	std::vector<std::string>::iterator it = std::find(classes.begin(), classes.end(), _class);
	if (it == classes.end()) return;
	classes.erase(it);
	return;
}
bool ElementID::has_class(std::string _class)
{
	std::vector<std::string>::iterator it = std::find(classes.begin(), classes.end(), _class);
	if (it == classes.end()) return false;
	return true;
}
std::string ElementID::get_id_info_str()
{
	std::ostringstream ss;
	ss << "ID: \"" << id << "\"\n";
	ss << "classes \n{";
	for (unsigned i=0; i<classes.size(); i++)
	{
		ss << "   \"" << classes[i] << "\"\n";
	}
	ss << "}";
	return ss.str();
}
