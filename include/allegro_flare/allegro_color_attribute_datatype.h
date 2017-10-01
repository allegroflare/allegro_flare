#pragma once



#include <allegro5/allegro_color.h>
#include <string>



struct AllegroColorAttributeDatatype
{
public:
   ALLEGRO_COLOR color;

   static bool to_val_func(void *val, std::string str);
   static std::string to_str_func(void *val);
};



