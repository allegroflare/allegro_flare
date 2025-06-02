#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Camera3D
   {
   public:
      float near_plane;
      float far_plane;

      AllegroFlare::Vec3D position;
      AllegroFlare::Vec3D stepout;
      float spin;
      float tilt;
      float roll;
      float zoom;

      bool spin_in_unit_values;
      bool tilt_in_unit_values;
      bool roll_in_unit_values;

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

      void use_unit_values();
      void use_radian_values();

      float get_near_plane();
      void set_near_plane(float near_plane=1);
      float get_far_plane();
      void set_far_plane(float far_plane=100);

      AllegroFlare::Vec3D calculate_strafe_vector_xz();
      void strafe_xy(float displacement=0.0f);
      AllegroFlare::Vec3D get_viewing_direction();
      AllegroFlare::Vec3D get_reverse_viewing_direction();

      void blend(AllegroFlare::Camera3D* other, float interpolation=0.1f); 
   };
}


