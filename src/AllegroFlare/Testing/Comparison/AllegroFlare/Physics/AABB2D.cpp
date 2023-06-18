

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/AABB2D.hpp>


namespace AllegroFlare::Physics
{


bool operator==(const AABB2D& object, const AABB2D& other_object)
{
   //if (object.x != other_object.x) return false;
   //if (object.y != other_object.y) return false;
   return true;
}


void PrintTo(const AABB2D& object, ::std::ostream* os)
{
   *os << "AllegroFlare::Physics::AABB2D("
       << "x: " << object.get_x()
       << ", "
       << "y: " << object.get_y()
       << ", "
       << "w: " << object.get_w()
       << ", "
       << "h: " << object.get_h()
       << ", "
       << "velocity_x: " << object.get_velocity_x()
       << ", "
       << "velocity_y: " << object.get_velocity_y()
       <<
   ")";
}


}


