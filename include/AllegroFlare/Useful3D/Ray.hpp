#pragma once


#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Useful3D
   {
      class Ray
      {
      public:
         AllegroFlare::vec3d orig;
         AllegroFlare::vec3d dir;

         Ray(AllegroFlare::vec3d orig={}, AllegroFlare::vec3d dir={});
      };
   } // namespace Useful3D
} // namespace AllegroFlare


