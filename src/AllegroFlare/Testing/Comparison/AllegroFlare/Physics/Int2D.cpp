

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>


namespace AllegroFlare::Physics
{


bool operator==(const Int2D& object, const Int2D& other_object)
{
   if (object.get_x() != other_object.get_x()) return false;
   if (object.get_y() != other_object.get_y()) return false;
   return true;
}


void PrintTo(const Int2D& object, ::std::ostream* os)
{
   *os << "Physics::Int2(" << object.get_x() << ", " << object.get_y() << ")";
}


}


