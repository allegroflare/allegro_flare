

#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>



namespace AllegroFlare
{


bool operator==(const ALLEGRO_VERTEX_WITH_NORMAL& object, const ALLEGRO_VERTEX_WITH_NORMAL& other_object)
{
   //if (object.x != other_object.x) return false;
   //if (object.y != other_object.y) return false;
   return true;
}


void PrintTo(const ALLEGRO_VERTEX_WITH_NORMAL& object, ::std::ostream* os)
{
   // TODO: Add COLOR
   *os << "ALLEGRO_VERTEX_WITH_NORMAL("
       << "x:" << object.x << ", "
       << "y:" << object.y << ", "
       << "z:" << object.z << ", "
       << "u:" << object.u << ", "
       << "v:" << object.v << ", "
       << "nx:" << object.nx << ", "
       << "ny:" << object.ny << ", "
       << "nz:" << object.nz << ", "
   ")";
}


}


