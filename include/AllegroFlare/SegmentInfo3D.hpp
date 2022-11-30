#pragma once


#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   class SegmentInfo3D
   {
   public:
      AllegroFlare::Vec3D start;
      AllegroFlare::Vec3D end;
      AllegroFlare::Vec3D from_start;
      AllegroFlare::Vec3D perpendicular;
      AllegroFlare::Vec3D normal;
      AllegroFlare::Vec3D middle;
      float radius;
      float length;

      SegmentInfo3D() {}
      SegmentInfo3D(AllegroFlare::Vec3D &start, AllegroFlare::Vec3D &end);
   };
}


