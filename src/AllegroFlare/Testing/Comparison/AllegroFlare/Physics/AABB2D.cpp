

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/AABB2D.hpp>


namespace AllegroFlare::Physics
{


bool operator==(const AABB2D& object, const AABB2D& other_object)
{
   // TODO: Fill in these operations
   if (object.get_x() != other_object.get_x()) return false;
   if (object.get_y() != other_object.get_y()) return false;
   if (object.get_w() != other_object.get_w()) return false;
   if (object.get_h() != other_object.get_h()) return false;
   if (object.get_velocity_x() != other_object.get_velocity_x()) return false;
   if (object.get_velocity_y() != other_object.get_velocity_y()) return false;
   return true;
}


bool operator!=(const AABB2D& object, const AABB2D& other_object)
{
   return !(object == other_object);
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


