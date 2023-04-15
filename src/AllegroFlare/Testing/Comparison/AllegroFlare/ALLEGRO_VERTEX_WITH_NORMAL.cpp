

#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>



namespace AllegroFlare
{


bool operator==(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object)
{
   if (object.x != other_object.x) return false;
   if (object.y != other_object.y) return false;
   if (object.z != other_object.z) return false;

   if (object.u != other_object.u) return false;
   if (object.v != other_object.v) return false;

   if (object.color != other_object.color) return false;

   if (object.nx != other_object.nx) return false;
   if (object.ny != other_object.ny) return false;
   if (object.nz != other_object.nz) return false;
   return true;
}


bool operator!=(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object)
{
   return !(object == other_object);
}


void PrintTo(const ALLEGRO_VERTEX_WITH_NORMAL& object, ::std::ostream* os)
{
   // TODO: Add COLOR
   *os << "ALLEGRO_VERTEX_WITH_NORMAL("
       << "x:" << object.x << ", "
       << "y:" << object.y << ", "
       << "z:" << object.z << ", "
       << "u:" << object.u << ", "
       << "v:" << object.v << ", ";

   PrintTo(object.color, os);
   *os << ", ";

   *os << "nx:" << object.nx << ", "
       << "ny:" << object.ny << ", "
       << "nz:" << object.nz << ", "
   ")";
}


}


