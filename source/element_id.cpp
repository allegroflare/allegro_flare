


#include <allegro_flare/element_id.h>
#include <allegro_flare/console_color.h>


ElementID::ElementID(ElementID *parent)
   : Attributes()
   , id(next_unique_id++)
   , parent(parent)
   , children()
{
   if (parent) parent->children.push_back(this);
}


ElementID::~ElementID()
{
   for (auto &child : children) delete child;
}


int ElementID::get_id()
{
   return id;
}


int ElementID::num_children()
{
   return children.size();
}


ElementID *ElementID::find_first(std::string attribute)
{
   for (auto &child : children)
      if (child->exists(attribute)) return child;
   return NULL;
}


ElementID *ElementID::find_first(std::string attribute, std::string value)
{
   for (auto &child : children)
      if (child->exists(attribute, value)) return child;
   return NULL;
}


int ElementID::next_unique_id = 1;


