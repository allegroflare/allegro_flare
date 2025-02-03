

#include <AllegroFlare/Useful3D/Useful3D.hpp>


#include <AllegroFlare/Useful.hpp> // for dot_product (and likely other things)
#include <math.h> // for fabs


// NOTE: For some reason, The archiver `ar`, `randlib` at compile-time thinks this class contains no objects. It's
// possible the Useful3D namespace could be appearing in other locations and with duplicate symbols. To silence the
// warnings, AllegroFlare/HeaderOnly.hpp is included below.
// TODO: Review why the archiver thinks there are no symbols in this class (see note above).
#include <AllegroFlare/HeaderOnly.hpp>


namespace AllegroFlare
{
namespace Useful3D
{

   bool intersectPlane(
         const AllegroFlare::vec3d &n,
         const AllegroFlare::vec3d &p0,
         const AllegroFlare::vec3d& l0,
         const AllegroFlare::vec3d &l,
         float &d
      )
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


   void draw_3d_line(AllegroFlare::vec3d start, AllegroFlare::vec3d end, ALLEGRO_COLOR col)
   {
      ALLEGRO_VERTEX vtx[2];
      vtx[0] = AllegroFlare::build_vertex(start.x, start.y, start.z, col, 0, 0);
      vtx[1] = AllegroFlare::build_vertex(end.x, end.y, end.z, col, 0, 0);
      al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
   }




   ALLEGRO_VERTEX create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col)
   {
      return AllegroFlare::build_vertex(vec.x, vec.y, vec.z, col, 0, 0);
   }




   AllegroFlare::vec3d centroid(AllegroFlare::vec3d v1, AllegroFlare::vec3d v2, AllegroFlare::vec3d v3)
   {
      return (v1 + v2 + v3) / 3;
   }




   AllegroFlare::vec3d tovec3d(ALLEGRO_VERTEX v1)
   {
      return AllegroFlare::vec3d(v1.x, v1.y, v1.z);
   }




   AllegroFlare::vec3d centroid(
         AllegroFlare::vec3d v1,
         AllegroFlare::vec3d v2,
         AllegroFlare::vec3d v3,
         AllegroFlare::vec3d v4
      )
   {
      return (v1 + v2 + v3 + v4) / 4;
   }




   void draw_3d_triangle(
         AllegroFlare::vec3d v1,
         AllegroFlare::vec3d v2,
         AllegroFlare::vec3d v3,
         ALLEGRO_COLOR col
      )
   {
      ALLEGRO_VERTEX vtx[3];
      vtx[0] = create_vtx(v1, col);
      vtx[1] = create_vtx(v2, col);
      vtx[2] = create_vtx(v3, col);
      al_draw_prim(vtx, NULL, NULL, 0, 3, ALLEGRO_PRIM_TRIANGLE_FAN);
   }




   bool basically_equal(const AllegroFlare::vec3d &first, const AllegroFlare::vec3d &other, float threshold)
   {
      return fabs(first.x - other.x) < threshold
          && fabs(first.y - other.y) < threshold
          && fabs(first.z - other.z) < threshold;
   }



}
}


