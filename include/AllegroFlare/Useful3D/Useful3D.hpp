#pragma once


#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
namespace Useful3D
{


   static bool intersectPlane(
         const AllegroFlare::vec3d &n,
         const AllegroFlare::vec3d &p0,
         const AllegroFlare::vec3d& l0,
         const AllegroFlare::vec3d &l,
         float &d
      );


}
}



