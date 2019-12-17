


#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Frustum.hpp>
#include <AllegroFlare/Useful.hpp>



namespace AllegroFlare
{
   Camera3D::Camera3D(AllegroFlare::vec3d position, AllegroFlare::vec3d view_vector, AllegroFlare::vec3d up_vector)
      : camera_tracking_mode(Camera3D::CAMERA_VIEW_THIRD_PERSON_HIGH)
      , position(position)
      , view_vector(view_vector)
      , up_vector(up_vector)
      , pitch(0)
      , stepback(0)
      , stepback_pitch(0)
      , stepback_rotation(0)
   {}




   void Camera3D::update_camera_tracking(AllegroFlare::vec3d targets_position, AllegroFlare::vec3d targets_view_vector)
   {
      AllegroFlare::vec3d view_vec(0, 0, 0);

      switch(camera_tracking_mode)
      {
      case CAMERA_VIEW_THIRD_PERSON_HIGH:
         // a nice, semi angled birds eye view:
         is_fixed_on_axis = false;
         position = targets_position;
         stepback = targets_view_vector * -3;
         stepback += AllegroFlare::vec3d(0, 5, 0); // ascent
         stepback_pitch = -0.6;
         pitch = 0;
         view_vector = targets_view_vector;
         break;
      case CAMERA_VIEW_THIRD_PERSON:
         // a nice third person view:
         is_fixed_on_axis = false;
         position = targets_position;
         stepback = targets_view_vector * -3;
         stepback += AllegroFlare::vec3d(0, 2, 0); // ascent
         stepback_pitch = -0.05;
         pitch = 0;
         view_vector = targets_view_vector;
         break;
      case CAMERA_VIEW_FRIST_PERSON:
         // a first person view:
         is_fixed_on_axis = false;
         position = targets_position;
         stepback = 0;
         stepback += AllegroFlare::vec3d(0, 1.25, 0); // ascent
         stepback_pitch = 0.2;
         //pitch = 0; // in first person, pitch is controlled by the mouse
         view_vector = targets_view_vector;
         break;
      case CAMERA_VIEW_TRACK_ALONG_X:
         // a first person view:
         is_fixed_on_axis = true;
         position = targets_position;
         view_vec = AllegroFlare::vec3d(0, 0, -1);
         stepback = view_vec * -10;
         stepback += AllegroFlare::vec3d(0, 5, 0); // ascent
         stepback_pitch = -0.05;
         pitch = 0;
         view_vector = view_vec;
         break;
      case CAMERA_VIEW_TRACK_ALONG_X_HIGH:
         // a first person view:
         is_fixed_on_axis = true;
         position = targets_position;
         view_vec = AllegroFlare::vec3d(0, 0, -1);
         stepback = view_vec * -12;
         stepback += AllegroFlare::vec3d(0, 10, 0); // ascent
         pitch = 0;
         stepback_pitch = -0.5;
         view_vector = view_vec;
         break;
      case CAMERA_VIEW_TRACK_ALONG_X_BIRD:
         // a first person view:
         is_fixed_on_axis = true;
         position = targets_position;
         view_vec = AllegroFlare::vec3d(0, 0, -1);
         stepback = view_vec * -8;
         stepback += AllegroFlare::vec3d(0, 12, 0); // ascent
         pitch = 0;
         stepback_pitch = -1.0;
         view_vector = view_vec;
         break;
      }
   }




   // might want to rename this function to something else
   void Camera3D::set_frustum_as_camera(ALLEGRO_DISPLAY *d)
   {
      if (!d) return;




      /// hrmkay...
      al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
      al_clear_depth_buffer(1); 



      // assemble the appropriate transform


      ALLEGRO_TRANSFORM transform;

      al_identity_transform(&transform);

      al_translate_transform_3d(&transform, -position.x-stepback.x, -position.y-stepback.y, -position.z-stepback.z);

      AllegroFlare::vec2d thing(view_vector.x, view_vector.z);
      al_rotate_transform_3d(&transform, 0, 1, 0, thing.get_angle() + AllegroFlare::TAU/4);
      al_rotate_transform_3d(&transform, 0, 1, 0, stepback_rotation.y); //  tilt the camera to look downward slightly
      al_rotate_transform_3d(&transform, -1, 0, 0, stepback_pitch + pitch); //  the up-down tilt of the camera



      // setup projection


      Frustum frustum(al_get_display_width(d), al_get_display_height(d), 500, 0.0001);

      al_perspective_transform(&transform,
            frustum.left, frustum.top, frustum.znear,
            frustum.right, frustum.bottom, frustum.zfar);


      al_use_projection_transform(&transform);
   }




   void Camera3D::look_at(AllegroFlare::vec3d target)
   {
      view_vector = (target - position).normalized();
   }
}



