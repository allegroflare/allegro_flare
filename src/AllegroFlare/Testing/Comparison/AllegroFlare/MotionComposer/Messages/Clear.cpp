

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/Clear.hpp>


namespace AllegroFlare::MotionComposer::Messages
{


  bool operator==(const Clear& object, const Clear& other_object)
  {
     //if (object.x != other_object.x) return false;
     //if (object.y != other_object.y) return false;
     return true;
  }


  void PrintTo(const Clear& object, ::std::ostream* os)
  {
     //*os << "Vec2D(" << object.x << ", " << object.y << ")";
  }


}


