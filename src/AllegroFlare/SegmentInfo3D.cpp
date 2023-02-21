
#include <AllegroFlare/SegmentInfo3D.hpp>


#include <AllegroFlare/Useful.hpp> // for distance


namespace AllegroFlare
{
   SegmentInfo3D::SegmentInfo3D(AllegroFlare::Vec3D &start, AllegroFlare::Vec3D &end)
   {
      this->start = start;
      this->end = end;
      from_start = end - start;
      tangent_vector = from_start.normalized();
      middle = from_start/2 + start; // TODO: address: divide by 2?
      length = distance(start, end);
      radius = length/2; // TODO: address: divide by 2?
      // TODO: create a perpendicular for this class
      //perpendicular = AllegroFlare::Vec3D(-from_start.y, from_start.x);
      //normal = ~-perpendicular;
   }
}



