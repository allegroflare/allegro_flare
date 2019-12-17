#pragma once


namespace AllegroFlare
{
   struct Frustum
   {
   public:
      float znear, zfar;
      float top, left, right, bottom;

      Frustum(int width=800, int height=600, int znear=500, float multiplier=0.01);
   };
}



