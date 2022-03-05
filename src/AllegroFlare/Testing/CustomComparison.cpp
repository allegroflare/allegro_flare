
#include <AllegroFlare/Testing/CustomComparison.hpp>


void PrintTo(const ALLEGRO_COLOR& color, ::std::ostream* os)
{
  *os << "ALLEGRO_COLOR{" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "}";
}

bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color)
{
   if (color.r != other_color.r) return false;
   if (color.g != other_color.g) return false;
   if (color.b != other_color.b) return false;
   if (color.a != other_color.a) return false;
   return true;
}

bool operator==(const AllegroFlare::vec2d& vec, const AllegroFlare::vec2d& other_vec)
{
   if (vec.x != other_vec.x) return false;
   if (vec.y != other_vec.y) return false;
   return true;
}

namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::vec2d& vec, ::std::ostream* os)
   {
      *os << "AllegroFlare::vec2d(" << vec.x << ", " << vec.y << ")";
   }
}

