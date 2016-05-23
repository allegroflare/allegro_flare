#ifndef __AF_ELEMENT_ID_HEADER
#define __AF_ELEMENT_ID_HEADER



#include <vector>
#include <allegro_flare/attributes.h>

class ElementID : public Attributes
{
private:
   static int next_unique_id;
   int id;
   ElementID *parent;
   std::vector<ElementID *> children;

public:
   ElementID(ElementID *parent);
   ~ElementID();

   int get_id();
};




#endif
