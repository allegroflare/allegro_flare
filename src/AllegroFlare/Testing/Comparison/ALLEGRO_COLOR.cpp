

#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color)
{
   if (color.r != other_color.r) return false;
   if (color.g != other_color.g) return false;
   if (color.b != other_color.b) return false;
   if (color.a != other_color.a) return false;
   return true;
}


void PrintTo(const ALLEGRO_COLOR& color, ::std::ostream* os)
{
  *os << "ALLEGRO_COLOR{" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "}";
}


