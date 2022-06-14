#pragma once


#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h> // for ALLEGRO_TRANSFORM


namespace AllegroFlare
{
   class Camera3D
   {
   public:
      AllegroFlare::vec3d position;
      AllegroFlare::vec3d stepout;
      float spin;
      float tilt;
      float zoom;

      Camera3D();
      ~Camera3D();

      void position_transform(ALLEGRO_TRANSFORM *t);
      void reverse_position_transform(ALLEGRO_TRANSFORM *t);
      AllegroFlare::vec3d get_real_position();
      void setup_projection_on(ALLEGRO_BITMAP *surface);
   };
}


