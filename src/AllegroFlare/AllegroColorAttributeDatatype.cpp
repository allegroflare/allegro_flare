


#include <AllegroFlare/AllegroColorAttributeDatatype.hpp>
#include <sstream>



namespace AllegroFlare
{
   bool AllegroColorAttributeDatatype::to_val_func(void *val, std::string str)
   {
      AllegroColorAttributeDatatype &d = *static_cast<AllegroColorAttributeDatatype *>(val);
      std::stringstream ss(str);
      ss >> d.color.r;
      ss >> d.color.g;
      ss >> d.color.b;
      ss >> d.color.a;
      return true;
   }



   std::string AllegroColorAttributeDatatype::to_str_func(void *val)
   {
      AllegroColorAttributeDatatype &d = *static_cast<AllegroColorAttributeDatatype *>(val);
      std::stringstream ss;
      ss << d.color.r << " " << d.color.g << " " << d.color.b << " " << d.color.a;
      return ss.str();
   }



   const std::string AllegroColorAttributeDatatype::IDENTIFIER = "ALLEGRO_COLOR";
}



