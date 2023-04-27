

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{


void PrintTo(const AllegroFlare::Vec2D& vec, ::std::ostream* os)
{
   *os << "AllegroFlare::Vec2D(" << vec.x << ", " << vec.y << ")";
}


}


