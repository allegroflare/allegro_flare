

#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>



namespace AllegroFlare
{


bool operator==(
      const ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL& object,
      const ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL& other_object
   )
{
   if (object.x != other_object.x) return false;
   if (object.y != other_object.y) return false;
   if (object.z != other_object.z) return false;

   if (object.u1 != other_object.u1) return false;
   if (object.v1 != other_object.v1) return false;
   if (object.u2 != other_object.u2) return false;
   if (object.v2 != other_object.v2) return false;

   if (object.color != other_object.color) return false;

   if (object.nx != other_object.nx) return false;
   if (object.ny != other_object.ny) return false;
   if (object.nz != other_object.nz) return false;
   return true;
}


bool operator!=(
      const ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL& object,
      const ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL& other_object
   )
{
   return !(object == other_object);
}


void PrintTo(const ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL& object, ::std::ostream* os)
{
   // TODO: Add COLOR
   *os << "ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL("
       << "x:" << object.x << ", "
       << "y:" << object.y << ", "
       << "z:" << object.z << ", "
       << "u1:" << object.u1 << ", "
       << "v1:" << object.v1 << ", "
       << "u2:" << object.u2 << ", "
       << "v2:" << object.v2 << ", "
       ;

   PrintTo(object.color, os);
   *os << ", ";

   *os << "nx:" << object.nx << ", "
       << "ny:" << object.ny << ", "
       << "nz:" << object.nz << ", "
   ")";
}


} // namespace AllegroFlare


