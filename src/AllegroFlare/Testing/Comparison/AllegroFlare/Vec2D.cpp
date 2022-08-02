

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


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
}


