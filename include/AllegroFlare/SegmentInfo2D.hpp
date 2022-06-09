#pragma once


#include <AllegroFlare/Vec2D.hpp>


namespace AllegroFlare
{
   class SegmentInfo2D
   {
   public:
      AllegroFlare::vec2d start;
      AllegroFlare::vec2d end;
      AllegroFlare::vec2d from_start;
      AllegroFlare::vec2d perpendicular;
      AllegroFlare::vec2d normal;
      AllegroFlare::vec2d middle;
      float radius;
      float length;

      SegmentInfo2D() {}
      SegmentInfo2D(AllegroFlare::vec2d &start, AllegroFlare::vec2d &end);
   };
}



