#pragma once



#include <allegro5/allegro.h>
#include <AllegroFlare/Frustum.hpp>
#include <AllegroFlare/Vec3D.hpp>



namespace AllegroFlare
{
   struct camera_tracking_setting // TODO: <-this
   {

   };




   class Camera3D
   {
   public:
      enum camera_tracking_mode_t
      {
         CAMERA_VIEW_DIRECT = 0,
         CAMERA_VIEW_THIRD_PERSON_HIGH,
         CAMERA_VIEW_THIRD_PERSON,
         CAMERA_VIEW_FRIST_PERSON,
         CAMERA_VIEW_TRACK_ALONG_X, // platform game style
         CAMERA_VIEW_TRACK_ALONG_X_HIGH, // sim city style :)
         CAMERA_VIEW_TRACK_ALONG_X_BIRD, // sim city style :)
         CAMERA_VIEW_LAST // for mod
      };

      bool is_fixed_on_axis; // so, the controls will change when the camera is fixed along an axis (CAMERA_VIEW_TRACK_ALONG_X, etc)
                             // When in first person (or in camera views where the camera is always behind the head of the player),
                             // then UP is forward, DOWN is backward, LEFT turns left and RIGHT turns right.
                             // When the camera is fixed on an axis, then the player's direction will be the direction that the 
                             // input points.

      int camera_tracking_mode;

      AllegroFlare::vec3d position;
      AllegroFlare::vec3d view_vector;
      AllegroFlare::vec3d up_vector;
      float pitch;

      //camera_tracking_mode_t camera_tracking_mode;

      // hmm, these I think might crave to be implemented in a better way:
      AllegroFlare::vec3d stepback;
      float stepback_pitch;
      AllegroFlare::vec3d stepback_rotation;

      Camera3D(AllegroFlare::vec3d position, AllegroFlare::vec3d view_vector=AllegroFlare::vec3d(0, 0, 1), AllegroFlare::vec3d up_vector=AllegroFlare::vec3d(0, 1, 0)); // yea, up vector should be positive
      void set_frustum_as_camera(ALLEGRO_DISPLAY *d);

      void look_at(AllegroFlare::vec3d target);
      void update_camera_tracking(AllegroFlare::vec3d targets_position, AllegroFlare::vec3d targets_view_vector);

      Frustum get_frustum(ALLEGRO_DISPLAY *d);
   };
}



