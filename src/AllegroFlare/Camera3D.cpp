


#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Frustum.hpp>
#include <AllegroFlare/Useful.hpp>



namespace AllegroFlare
{
   Camera3D::Camera3D(AllegroFlare::vec3d position, AllegroFlare::vec3d view_vector, AllegroFlare::vec3d up_vector)
      : position(position)
      , view_vector(view_vector)
      , up_vector(up_vector)
      , pitch(0)
      , stepback(0)
      , stepback_pitch(0)
      , stepback_rotation(0)
   {}


   void Camera3D::start_transform()
   {
      // create the view transform
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_translate_transform_3d(&transform, -position.x-stepback.x, -position.y-stepback.y, -position.z-stepback.z);
      AllegroFlare::vec2d thing(view_vector.x, view_vector.z);
      al_rotate_transform_3d(&transform, 0, 1, 0, thing.get_angle() + AllegroFlare::TAU/4);
      al_rotate_transform_3d(&transform, 0, 1, 0, stepback_rotation.y); //  tilt the camera to look downward slightly
      al_rotate_transform_3d(&transform, -1, 0, 0, stepback_pitch + pitch); //  the up-down tilt of the camera


      ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
      if (!target_bitmap) throw std::runtime_error("[Camera3D:start_transform]: cannot set on a nullptr target_bitmap");



      int width = al_get_bitmap_width(target_bitmap);
      int height = al_get_bitmap_height(target_bitmap);



      // setup projection
      Frustum frustum(width, height, 500, 0.0001);
      al_perspective_transform(&transform,
            frustum.left, frustum.top, frustum.znear,
            frustum.right, frustum.bottom, frustum.zfar);
      al_use_projection_transform(&transform);
   }


   // might want to rename this function to something else
   void Camera3D::clear_screen_and_start_transform_on_current_bitmap()
   {
      /// hrmkay...
      al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
      al_clear_depth_buffer(1); 


      al_clear_to_color(al_color_name("maroon"));



      // assemble the appropriate transform
      start_transform();
   }




   void Camera3D::look_at(AllegroFlare::vec3d target)
   {
      view_vector = (target - position).normalized();
   }
}



