

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


namespace AllegroFlare::MotionComposer::Messages
{


  bool operator==(const AddActor2D& object, const AddActor2D& other_object)
  {
     //if (object.x != other_object.x) return false;
     //if (object.y != other_object.y) return false;
     return true;
  }


  void PrintTo(const AddActor2D& object, ::std::ostream* os)
  {
     //*os << "AddActor2D(" << object.x << ", " << object.y << ")";
  }


}


