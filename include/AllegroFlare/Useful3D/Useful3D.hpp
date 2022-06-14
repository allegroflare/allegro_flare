#pragma once


#include <AllegroFlare/Vec3D.hpp>

#include <allegro5/allegro.h> // for ALLEGRO_COLOR
#include <allegro5/allegro_primitives.h> // for ALLEGRO_VERTEX
#include <AllegroFlare/Color.hpp>


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
   static void draw_3d_line(
      AllegroFlare::vec3d start,
      AllegroFlare::vec3d end,
      ALLEGRO_COLOR col=AllegroFlare::color::red
   );
   static ALLEGRO_VERTEX create_vtx(AllegroFlare::vec3d vec, ALLEGRO_COLOR col);
   static AllegroFlare::vec3d centroid(AllegroFlare::vec3d v1, AllegroFlare::vec3d v2, AllegroFlare::vec3d v3);
   static AllegroFlare::vec3d tovec3d(ALLEGRO_VERTEX v1);
   static AllegroFlare::vec3d centroid(
      AllegroFlare::vec3d v1,
      AllegroFlare::vec3d v2,
      AllegroFlare::vec3d v3,
      AllegroFlare::vec3d v4
   );
   static void draw_3d_triangle(
      AllegroFlare::vec3d v1,
      AllegroFlare::vec3d v2,
      AllegroFlare::vec3d v3,
      ALLEGRO_COLOR col
   );
   static bool basically_equal(
      const AllegroFlare::vec3d &first,
      const AllegroFlare::vec3d &other,
      float threshold
   );

} // namespace Useful3D
} // namespace AllegroFlare



