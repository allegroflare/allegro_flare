

#include <AllegroFlare/Useful.hpp> // for dot_product (and likely other things)
#include <AllegroFlare/Useful3D/Useful3D.hpp>


namespace AllegroFlare
{
namespace Useful3D
{

   static bool intersectPlane(const AllegroFlare::vec3d &n, const AllegroFlare::vec3d &p0, const AllegroFlare::vec3d& l0, const AllegroFlare::vec3d &l, float &d)
   {
      // assuming vectors are all normalized
      float denom = dot_product(n, l);
      if (denom > 1e-6) {
         AllegroFlare::vec3d p0l0 = p0 - l0;
         d = dot_product(p0l0, n) / denom;
         return (d >= 0);
      }
      return false;
   }


}
}


