



#include <AllegroFlare/ElementID.hpp>

#include <AllegroFlare/ConsoleColor.hpp>




namespace AllegroFlare
{
   void ElementID::add_child(ElementID *child)
   {
      children.push_back(child);
   }




   bool ElementID::remove_child(ElementID *child)
   {
      int index = get_index_of_child(child);
      if (index == -1) return false;
      children.erase(children.begin() + index);
      return true;
   }




   ElementID::ElementID(ElementID *parent)
      : Attributes()
      , id(next_unique_id++)
      , parent(parent)
      , children()
   {
      if (parent) parent->add_child(this);
   }




   ElementID::~ElementID()
   {
      while(children.size() > 0) delete children[0];
      if (parent) parent->remove_child(this);
   }




   int ElementID::get_id()
   {
      return id;
   }




   ElementID *ElementID::get_parent()
   {
      return parent;
   }




   bool ElementID::has_parent()
   {
      return parent != nullptr;
   }




   void ElementID::reassign_parent(ElementID *new_parent)
   {
      if (new_parent == parent) return;
      if (parent) parent->remove_child(this);
      if (new_parent) new_parent->add_child(this);
      parent = new_parent;
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




   bool ElementID::has_children()
   {
      return !children.empty();
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




   ElementID *ElementID::find_first_descendant(std::string attribute)
   {
      for (auto &child : children)
      {
         if (child->exists(attribute)) return child;
         ElementID *child_descendant = child->find_first_descendant(attribute);
         if (child_descendant) return child_descendant;
      }
      return NULL;
   }




   ElementID *ElementID::find_first_descendant(std::string attribute, std::string value)
   {
      for (auto &child : children)
      {
         if (child->exists(attribute, value)) return child;
         ElementID *child_descendant = child->find_first_descendant(attribute, value);
         if (child_descendant) return child_descendant;
      }
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




   // used internally for recursively counting nodes in the tree
   int ElementID::__index_count_r;
   ElementID *ElementID::__get_nth_descendant_r(std::vector<ElementID *> &children, int n)
   {
      for (ElementID *child : children)
      {
         __index_count_r++;
         if (__index_count_r == n) return child;
         ElementID *element = __get_nth_descendant_r(child->children, n);
         if (element) return element;
      }
      return NULL;
   }




   ElementID *ElementID::get_nth_descendant(int num)
   {
      __index_count_r = -1;
      return __get_nth_descendant_r(children, num);
   }




   std::vector<ElementID *> ElementID::get_flat_list_of_descendants()
   {
      std::vector<ElementID *> elements;
      for (auto &child : children)
      {
         elements.push_back(child);
         std::vector<ElementID *> child_elements = child->get_flat_list_of_descendants();
         elements.insert(elements.end(), child_elements.begin(), child_elements.end());
      }
      return elements;
   }




   int ElementID::get_index_of_child(ElementID *child)
   {
      for (int i=0; i<children.size(); i++)
         if (children[i] == child) return i;
      return -1;
   }




   bool ElementID::is_child(ElementID *child)
   {
      return get_index_of_child(child) != -1;
   }




   bool ElementID::is_descendant(ElementID *descendant)
   {
      for (auto &child : children)
      {
         if (child == descendant) return true;
         if (child->is_descendant(descendant)) return true;
      }
      return false;
   }




   ElementID *ElementID::get_nth_child(int index)
   {
      if (index < 0 || index >= children.size()) return nullptr;
      return children[index];
   }




   ElementID *ElementID::get_random_child()
   {
      int random_int = rand() % children.size();
      return get_nth_child(random_int);
   }




   ElementID *ElementID::get_next_sibling()
   {
      if (!parent) return nullptr;
      int index = parent->get_index_of_child(this);
      if (index == -1) return nullptr;
      return parent->get_nth_child(index+1);
   }




   ElementID *ElementID::get_previous_sibling()
   {
      if (!parent) return nullptr;
      int index = parent->get_index_of_child(this);
      if (index == -1) return nullptr;
      return parent->get_nth_child(index-1);
   }




   bool ElementID::bring_child_to_front(ElementID *child)
   {
      int index = get_index_of_child(child);
      if (index == -1) return false;
      children.erase(children.begin() + index);
      children.insert(children.begin(), child);
      return true;
   }




   bool ElementID::send_child_to_back(ElementID *child)
   {
      int index = get_index_of_child(child);
      if (index == -1) return false;
      children.erase(children.begin() + index);
      children.push_back(child);
      return true;
   }




   std::vector<ElementID *> ElementID::get_children()
   {
      return children;
   }




   int ElementID::next_unique_id = 1;
}




