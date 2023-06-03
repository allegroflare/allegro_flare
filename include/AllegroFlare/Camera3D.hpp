#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h> // for ALLEGRO_TRANSFORM


namespace AllegroFlare
{
   class Camera3D
   {
   public:
      // camera and viewport settings
      float near_plane;
      float far_plane;

      // camera controls
      AllegroFlare::Vec3D position;
      AllegroFlare::Vec3D stepout;
      float spin;
      float tilt;
      float roll;
      float zoom;

      Camera3D();
      ~Camera3D();

      void position_transform(ALLEGRO_TRANSFORM *t);
      void reverse_position_transform(ALLEGRO_TRANSFORM *t);
      AllegroFlare::Vec3D get_real_position();
      void setup_projection_on(ALLEGRO_BITMAP *surface);
      AllegroFlare::Vec2D get_projected_coordinates(
         ALLEGRO_BITMAP *surface,
         float surface_width_num_units,
         float surface_height_num_units,
         float x,
         float y,
         float z
      );

      float get_near_plane();
      void set_near_plane(float near_plane=1);
      float get_far_plane();
      void set_far_plane(float far_plane=100);

      void strafe_xy(float displacement=0.0f);
   };
}


