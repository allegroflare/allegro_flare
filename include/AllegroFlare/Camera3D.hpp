#pragma once


#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h> // for ALLEGRO_TRANSFORM


namespace AllegroFlare
{
   class Camera3D
   {
   public:
      // camera and viewport settings
      float far_plane;

      // camera controls
      AllegroFlare::vec3d position;
      AllegroFlare::vec3d stepout;
      float spin;
      float tilt;
      float roll;
      float zoom;

      Camera3D();
      ~Camera3D();

      void position_transform(ALLEGRO_TRANSFORM *t);
      void reverse_position_transform(ALLEGRO_TRANSFORM *t);
      AllegroFlare::vec3d get_real_position();
      void setup_projection_on(ALLEGRO_BITMAP *surface);

      float get_far_plane();
      void set_far_plane(float far_plane=100);

      void strafe_xy(float displacement=0.0f);

      float squared_distance_from(float x, float y, float z);
      float squared_distance_from(AllegroFlare::Vec3D position);
   };
}


