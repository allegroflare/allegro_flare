

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>


namespace AllegroFlare::MotionComposer::Messages
{


  bool operator==(const AddActor2D& object, const AddActor2D& other_object)
  {
     if (object.get_identifier() != other_object.get_identifier()) return false;
     if (object.get_script() != other_object.get_script()) return false;
     return true;
  }


  bool operator!=(const AddActor2D& object, const AddActor2D& other_object)
  {
     return !(object == other_object);
  }


  void PrintTo(const AddActor2D& object, ::std::ostream* os)
  {
     *os << "AddActor2D(\"" << object.get_identifier() << "\", \"" << object.get_bitmap_identifier() << "\", \"" << object.get_script() << "\")";
  }


}


