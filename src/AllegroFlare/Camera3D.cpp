

#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Vec2D.hpp>

#include <algorithm>
#include <cmath>



namespace AllegroFlare
{



Camera3D::Camera3D()
   : position(0, 0, 0)
   , stepout(0, 0, 0)
   , spin(0)
   , tilt(0)
   , roll(0)
   , zoom(1.0) // note this is used in the scene renderer to setup the projection
{}



Camera3D::~Camera3D()
{}



void Camera3D::position_transform(ALLEGRO_TRANSFORM *t)
{
   al_identity_transform(t);

   al_translate_transform_3d(t, stepout.x, stepout.y, stepout.z);
   al_rotate_transform_3d(t, -1, 0, 0, tilt);
   al_rotate_transform_3d(t, 0, -1, 0, spin);
   al_rotate_transform_3d(t, 0, 0, -1, roll);
   al_translate_transform_3d(t, position.x, position.y, position.z);
}


void Camera3D::reverse_position_transform(ALLEGRO_TRANSFORM *t)
{
   // note: this is EXACTLY the same as position transform, except the
   // order of transformations is reversed, and the values are negated
   al_identity_transform(t);

   al_translate_transform_3d(t, -position.x, -position.y, -position.z);
   al_rotate_transform_3d(t, 0, 0, 1, roll);
   al_rotate_transform_3d(t, 0, 1, 0, spin);
   al_rotate_transform_3d(t, 1, 0, 0, tilt);
   al_translate_transform_3d(t, -stepout.x, -stepout.y, -stepout.z);
}


vec3d Camera3D::get_real_position()
{
   //vec3d real_position(0, 0, 0);
   vec3d real_position = position;
   ALLEGRO_TRANSFORM t;

   position_transform(&t);
   al_transform_coordinates_3d(&t, &real_position.x, &real_position.y, &real_position.z);

   return real_position;
}


void Camera3D::setup_projection_on(ALLEGRO_BITMAP *surface) // surface is usualy a backbuffer_sub_bitmap
{
   if (!surface) throw std::runtime_error("BBb");

   // set the target bitmap
   al_set_target_bitmap(surface);

   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);


   ALLEGRO_TRANSFORM t;

   reverse_position_transform(&t);

   float mul = 1.0 / zoom;
   float aspect_ratio = (float)al_get_bitmap_height(surface) / al_get_bitmap_width(surface);
   al_perspective_transform(&t, -1 * mul, aspect_ratio * mul, 1, 1 * mul, -aspect_ratio * mul, 100);

   al_use_projection_transform(&t);
}


void Camera3D::strafe_xy(float displacement)
{
   AllegroFlare::Vec2D move_vec(cos(spin), sin(spin));
   position.x += move_vec.x * displacement;
   position.y += 0;
   position.z += move_vec.y * displacement;
}



} // namespace AllegroFlare


