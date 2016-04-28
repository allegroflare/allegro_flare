#ifndef __ALLEGRO_FLARE_ELEMENT_ID_HEADER
#define __ALLEGRO_FLARE_ELEMENT_ID_HEADER




#include <algorithm>
#include <sstream>
#include <vector>




class ElementID;

class ElementIDManager
{
private:
   friend class ElementID;
   void add(ElementID *obj);
   void remove(ElementID *obj);

public:
   ElementIDManager();
   std::vector<ElementID *> elements;

   ElementID *get_element_by_id(std::string id);
   std::vector<ElementID *> get_elements_by_class(std::string class_name);
};




class ElementID
{
private:
   static int next_unique_id_num;

private:
   ElementIDManager *manager;
   int unique_id_num;
   std::string id;
   std::vector<std::string> classes;
   friend class ElementIDManager;

public:
   ElementID(ElementIDManager *manager);
   ~ElementID();

   void add_class(std::string _class);
   void remove_class(std::string _class);
   bool has_class(std::string _class);
   std::vector<std::string> get_classes() { return classes; }

   void set_id(std::string id);
   std::string get_id() { return id; }
   std::string get_id_info_str();
};



#endif
