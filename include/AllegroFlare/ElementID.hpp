#ifndef __AF_ELEMENT_ID_HEADER
#define __AF_ELEMENT_ID_HEADER




#include <vector>
#include <AllegroFlare/Attributes.hpp>




namespace AllegroFlare
{
   class ElementID : public Attributes
   {
   private:
      int id;
      ElementID *parent;
      std::vector<ElementID *> children;

      void add_child(ElementID *child);
      bool remove_child(ElementID *child);

   public:
      ElementID(ElementID *parent);
      virtual ~ElementID();

      int get_id();
      ElementID *get_parent();
      bool has_parent();
      ElementID *get_root();
      int num_children();
      bool has_children();
      int num_descendants();
      void reassign_parent(ElementID *new_parent);

      ElementID *find_first(std::string attribute);
      ElementID *find_first(std::string attribute, std::string value);
      ElementID *find_first_descendant(std::string attribute);
      ElementID *find_first_descendant(std::string attribute, std::string value);
      std::vector<ElementID *> find_all(std::string attribute);
      std::vector<ElementID *> find_all(std::string attribute, std::string value);
      std::vector<ElementID *> find_all_descendants(std::string attribute);
      std::vector<ElementID *> find_all_descendants(std::string attribute, std::string value);
      ElementID *get_nth_child(int index);
      ElementID *get_random_child();
      ElementID *get_nth_descendant(int num);
      ElementID *find_descendant_by_id(int id);
      std::vector<ElementID *> get_children();
      std::vector<ElementID *> get_flat_list_of_descendants();
      int get_index_of_child(ElementID *child);
      bool is_child(ElementID *child);
      bool is_descendant(ElementID *descendant);
      ElementID *get_next_sibling();
      ElementID *get_previous_sibling();

      bool bring_child_to_front(ElementID *child);
      bool send_child_to_back(ElementID *child);

      template<class T> // does not have tests
      std::vector<T *> get_flat_list_of_descendants()
      {
         std::vector<T *> elements;
         for (auto &child : children)
         {
            elements.push_back(static_cast<T *>(child));
            std::vector<T *> child_elements = child->get_flat_list_of_descendants<T>();
            elements.insert(elements.end(), child_elements.begin(), child_elements.end());
         }
         return elements;
      }

      template<class T> // does not have tests
      std::vector<T *> get_children()
      {
         std::vector<T *> elements;
         for (auto &child : children) elements.push_back(static_cast<T *>(child));
         return elements;
      }

      template<class T>
      static std::vector<T *> recast_collection(std::vector<ElementID *> collection)
      {
         std::vector<T *> recasted_collection;
         recasted_collection.reserve(collection.size());
         for (auto &element : collection) { recasted_collection.push_back(static_cast<T *>(element)); }
         return recasted_collection;
      }

   private:
      static int next_unique_id;
      static int __index_count_r;
      static ElementID *__get_nth_descendant_r(std::vector<ElementID *> &children, int num);
   };
}



#endif
