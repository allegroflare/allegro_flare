#include <AllegroFlare/SegmentInfo2D.hpp>


#include <AllegroFlare/Useful.hpp> // for distance


namespace AllegroFlare
{
   SegmentInfo2D::SegmentInfo2D(AllegroFlare::vec2d &start, AllegroFlare::vec2d &end)
   {
      this->start = start;
      this->end = end;
      from_start = end - start;
      middle = from_start/2 + start;
      length = distance(start, end);
      radius = length/2;
      perpendicular = AllegroFlare::vec2d(-from_start.y, from_start.x);
      normal = ~-perpendicular;
   }
}


