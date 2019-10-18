#pragma once



#include <allegro5/allegro_color.h>
#include <string>



namespace AllegroFlare
{
   struct AllegroColorAttributeDatatype
   {
   public:
      static const std::string IDENTIFIER;

      ALLEGRO_COLOR color;

      static bool to_val_func(void *val, std::string str);
      static std::string to_str_func(void *val);
   };
}



