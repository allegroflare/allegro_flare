


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


int ElementID::next_unique_id = 1;


