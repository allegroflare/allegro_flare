
#include <AllegroFlare/Testing/CustomComparison.hpp>

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
      *os << "AllegroFlare::vec2d(" << vec.x << ", " << vec.y << "}";
   }
}

