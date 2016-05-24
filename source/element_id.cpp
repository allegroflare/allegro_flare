


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


ElementID *ElementID::get_root()
{
   if (!parent) return NULL;
   ElementID *ancestor = parent;
   while (ancestor->parent) ancestor = ancestor->parent;
   return ancestor;
}


int ElementID::num_children()
{
   return children.size();
}


int ElementID::num_descendants()
{
   int count = 0;
   for (auto &child : children)
      count += child->num_descendants() + 1;
   return count;
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


std::vector<ElementID *> ElementID::find_all(std::string attribute)
{
   std::vector<ElementID *> results;
   for (auto &child : children)
      if (child->exists(attribute)) results.push_back(child);
   return results;
}


std::vector<ElementID *> ElementID::find_all(std::string attribute, std::string value)
{
   std::vector<ElementID *> results;
   for (auto &child : children)
      if (child->exists(attribute, value)) results.push_back(child);
   return results;
}


std::vector<ElementID *> ElementID::find_all_descendants(std::string attribute)
{
   std::vector<ElementID *> results;
   for (auto &child : children)
   {
      if (child->exists(attribute)) results.push_back(child);

      std::vector<ElementID *> child_descendants = child->find_all_descendants(attribute);
      results.insert(results.end(), child_descendants.begin(), child_descendants.end());
   }
   return results;
}


std::vector<ElementID *> ElementID::find_all_descendants(std::string attribute, std::string value)
{
   std::vector<ElementID *> results;
   for (auto &child : children)
   {
      if (child->exists(attribute, value)) results.push_back(child);

      std::vector<ElementID *> child_descendants = child->find_all_descendants(attribute, value);
      results.insert(results.end(), child_descendants.begin(), child_descendants.end());
   }
   return results;
}


ElementID *ElementID::find_descendant_by_id(int id_to_match)
{
   for (ElementID *child : children)
   {
      if (child->get_id() == id_to_match) return child;
      ElementID *child_return = child->find_descendant_by_id(id_to_match);
      if (child_return) return child_return;
   }
   return NULL;
}


int ElementID::next_unique_id = 1;


