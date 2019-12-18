#pragma once



#include <allegro5/allegro.h>
#include <AllegroFlare/Vec3D.hpp>



namespace AllegroFlare
{
   class Camera3D
   {
   private:
   public:
      AllegroFlare::vec3d position;
      AllegroFlare::vec3d view_vector;
      AllegroFlare::vec3d up_vector;
      float pitch;

      AllegroFlare::vec3d stepback;
      float stepback_pitch;
      AllegroFlare::vec3d stepback_rotation;

      Camera3D(AllegroFlare::vec3d position, AllegroFlare::vec3d view_vector=AllegroFlare::vec3d(0, 0, 1), AllegroFlare::vec3d up_vector=AllegroFlare::vec3d(0, 1, 0)); // yea, up vector should be positive
      void start_transform(ALLEGRO_DISPLAY *d);
      void clear_screen_and_start_transform(ALLEGRO_DISPLAY *d);

      void look_at(AllegroFlare::vec3d target);
   };
}



