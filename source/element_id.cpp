


#include <allegro_flare/element_id.h>




//
// ElementIDManager
//



ElementIDManager::ElementIDManager()
   : elements()
{}



void ElementIDManager::add(ElementID *obj) { elements.push_back(obj); }



void ElementIDManager::remove(ElementID *obj)
{
   // (fix this, it's linear)
   for (unsigned i=0; i<elements.size(); i++)
   {
      if (elements[i] == obj)
      {
         elements.erase(elements.begin()+i);
         return;
      }
   }
}



ElementID *ElementIDManager::get_element_by_id(std::string id)
{
   // (fix this, it's linear)
   for (unsigned i=0; i<elements.size(); i++)
   {
      if (elements[i]->id == id) return elements[i];
   }
   return NULL;
}



std::vector<ElementID *> ElementIDManager::get_elements_by_class(std::string class_name)
{
   std::vector<ElementID *> result;
   for (auto &e : elements)
      if (e->has_class(class_name)) result.push_back(e);
   return result;
}




//
// ElementID
//



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



std::vector<std::string> ElementID::get_classes()
{
   return classes;
}



std::string ElementID::get_id()
{
   return id;
}



std::string ElementID::to_string()
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



int ElementID::get_unique_id_num()
{
  return unique_id_num;
}

