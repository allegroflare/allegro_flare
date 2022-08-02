

#include <AllegroFlare/Testing/CustomComparison.hpp>


bool operator==(const AllegroFlare::Vec2D& vec, const AllegroFlare::Vec2D& other_vec)
{
   if (vec.x != other_vec.x) return false;
   if (vec.y != other_vec.y) return false;
   return true;
}


namespace AllegroFlare
{
   void PrintTo(const AllegroFlare::Vec2D& vec, ::std::ostream* os)
   {
      *os << "AllegroFlare::Vec2D(" << vec.x << ", " << vec.y << ")";
   }

   void PrintTo(const AllegroFlare::Color& color, ::std::ostream* os)
   {
      *os << "AllegroFlare::Color(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
   }
}

