

#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Logger.hpp>

#include <algorithm>
#include <stdexcept>
#include <cmath>




static float unit_to_radian(float unit_value)
{
   return unit_value * (ALLEGRO_PI * 2);
}


static float radian_to_unit(float radian_value)
{
   return radian_value / (ALLEGRO_PI * 2);
}


static float convert_to_match_system(
    float value_to_convert,
    bool is_value_in_units,
    bool target_system_is_units)
{
    if (is_value_in_units == target_system_is_units)
    {
        return value_to_convert; // Already in the target system
    }
    else if (target_system_is_units) // Target is units, so value_to_convert must be radians
    {
        return radian_to_unit(value_to_convert);
    }
    else // Target is radians, so value_to_convert must be units
    {
        return unit_to_radian(value_to_convert);
    }
}




namespace AllegroFlare
{



Camera3D::Camera3D()
   : near_plane(1)
   , far_plane(100)
   , position(0, 0, 0)
   , stepout(0, 0, 0)
   , spin(0.0f)
   , tilt(0.0f)
   , roll(0.0f)
   , zoom(1.0) // note this is used in the scene renderer to setup the projection
   , shift(0, 0)
   , spin_in_unit_values(false)
   , tilt_in_unit_values(false)
   , roll_in_unit_values(false)
{}



Camera3D::~Camera3D()
{}



void Camera3D::position_transform(ALLEGRO_TRANSFORM *t)
{
   al_identity_transform(t);

   al_translate_transform_3d(t, stepout.x, stepout.y, stepout.z);

   al_rotate_transform_3d(t, -1, 0, 0, tilt_in_unit_values ? unit_to_radian(tilt) : tilt);
   al_rotate_transform_3d(t, 0, -1, 0, spin_in_unit_values ? unit_to_radian(spin) : spin);
   al_rotate_transform_3d(t, 0, 0, -1, roll_in_unit_values ? unit_to_radian(roll) : roll);

   al_translate_transform_3d(t, position.x, position.y, position.z);
}



void Camera3D::reverse_position_transform(ALLEGRO_TRANSFORM *t)
{
   // note: this is EXACTLY the same as position transform, except the
   // order of transformations is reversed, and the values are negated
   al_identity_transform(t);

   al_translate_transform_3d(t, -position.x, -position.y, -position.z);

   al_rotate_transform_3d(t, 0, 0, 1, roll_in_unit_values ? unit_to_radian(roll) : roll);
   al_rotate_transform_3d(t, 0, 1, 0, spin_in_unit_values ? unit_to_radian(spin) : spin);
   al_rotate_transform_3d(t, 1, 0, 0, tilt_in_unit_values ? unit_to_radian(tilt) : tilt);

   al_translate_transform_3d(t, -stepout.x, -stepout.y, -stepout.z);
}



Vec3D Camera3D::get_real_position()
{
   //vec3D real_position(0, 0, 0);
   Vec3D real_position = position;
   ALLEGRO_TRANSFORM t;

   position_transform(&t);
   al_transform_coordinates_3d(&t, &real_position.x, &real_position.y, &real_position.z);

   return real_position;
}


void Camera3D::setup_projection_on(ALLEGRO_BITMAP *surface) // surface is usualy a backbuffer_sub_bitmap
{
    if (!surface)
    {
      throw std::runtime_error("Camera3D::setup_projection_on: surface cannot be nullptr.");
    }

    ALLEGRO_TRANSFORM t;

    reverse_position_transform(&t);

    /*
    float mul = near_plane / zoom;
    float aspect_ratio = (float)al_get_bitmap_height(surface) / al_get_bitmap_width(surface);

    // Calculate the frustum parameters, including the offset
    float left   = (-1.0f * mul) + shift.x;
    float right  = ( 1.0f * mul) + shift.x;
    float top    = ( aspect_ratio * mul) + shift.y;
    float bottom = (-aspect_ratio * mul) + shift.y;

    al_perspective_transform(&t, left, top, near_plane, right, bottom, far_plane);
    */

    float mul = near_plane / zoom;
    float aspect_ratio = (float)al_get_bitmap_height(surface) / al_get_bitmap_width(surface);

    // Interpret camera.shift.x and camera.shift.y as proportional factors
    // camera.shift.x = 1.0 means shift by one full current half-width
    // camera.shift.y = 1.0 means shift by one full current half-height
    float actual_world_offset_x = shift.x * mul;
    float actual_world_offset_y = shift.y * (mul * aspect_ratio);

    // Apply these calculated world offsets to the frustum boundaries
    float fr_left   = (-1.0f * mul) + actual_world_offset_x;
    float fr_right  = ( 1.0f * mul) + actual_world_offset_x;
    float fr_top    = ( aspect_ratio * mul) + actual_world_offset_y;    // Positive world_offset_y shifts frustum up, content appears down
    float fr_bottom = (-aspect_ratio * mul) + actual_world_offset_y;   // Positive world_offset_y shifts frustum up, content appears down

    al_perspective_transform(&t, fr_left, fr_top, near_plane, fr_right, fr_bottom, far_plane);


    // set the target bitmap
    al_set_target_bitmap(surface);

    // setup the render settings
    al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
    al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
    al_clear_depth_buffer(1); // TODO: PIPELINE: Look into removing this (as per your existing comment)

    al_use_projection_transform(&t);
}


AllegroFlare::Vec2D Camera3D::get_projected_coordinates(
      ALLEGRO_BITMAP *surface,
      float surface_width_num_units,
      float surface_height_num_units,
      float x,
      float y,
      float z
   )
{
   // TODO: "surface" is only needed so that it can be "use a projection transform" on, and then obtain
         // a "al_get_current_transform()" and "al_get_current_projection_transform" on
   // TODO: Confirm this does work as expected with more tests
   // TODO: Do not require setting up a projection on a surface
   // TODO: See if a "surface_width" and "surface_height" could be passed as arguments instead of a full "surface" 

   setup_projection_on(surface); // Also sets the target bitmap (as side effect, probably not wanted)

   ALLEGRO_TRANSFORM t2;
   al_copy_transform(&t2, al_get_current_transform());
   al_compose_transform(&t2, al_get_current_projection_transform());

   ALLEGRO_TRANSFORM t3;
   al_identity_transform(&t3);
   al_scale_transform(&t3, 0.5, -0.5);
   al_translate_transform(&t3, 0.5, 0.5);
   al_scale_transform(&t3, surface_width_num_units, surface_height_num_units);
   //al_scale_transform(&t3, al_get_bitmap_width(surface), al_get_bitmap_height(surface));
   //al_scale_transform(&t3, al_get_bitmap_width(al_get_target_bitmap()),
                      //al_get_bitmap_height(al_get_target_bitmap()));


   al_transform_coordinates_3d_projective(&t2, &x, &y, &z);
   // x, y now contain normalized coordinates
   al_transform_coordinates(&t3, &x, &y);
   // x, y now contain pixel coordinates

   return AllegroFlare::Vec2D(x, y);
}


float Camera3D::get_far_plane()
{
   return far_plane;
}


void Camera3D::set_far_plane(float far_plane)
{
   this->far_plane = far_plane;
}


float Camera3D::get_near_plane()
{
   return near_plane;
}


void Camera3D::set_near_plane(float near_plane)
{
   this->near_plane = near_plane;
}



AllegroFlare::Vec3D Camera3D::calculate_strafe_vector_xz()
{
   AllegroFlare::Vec2D move_vec(cos(spin), sin(spin));
   move_vec.normalized();
   return AllegroFlare::Vec3D(move_vec.x, 0, move_vec.y);
}


void Camera3D::strafe_xy(float displacement)
{
   AllegroFlare::Vec2D move_vec(cos(spin), sin(spin));
   position.x += move_vec.x * displacement;
   position.y += 0;
   position.z += move_vec.y * displacement;
}


AllegroFlare::Vec3D Camera3D::get_viewing_direction()
{
   ALLEGRO_TRANSFORM t;
   position_transform(&t);
   AllegroFlare::Vec3D stood_position(0, 0, 0); // TODO: Consider if this needs to be the stepout
   AllegroFlare::Vec3D stood_viewing_direction(0, 0, -1);
   al_transform_coordinates_3d(&t, &stood_position.x, &stood_position.y, &stood_position.z);
   al_transform_coordinates_3d(&t, &stood_viewing_direction.x, &stood_viewing_direction.y, &stood_viewing_direction.z);
   AllegroFlare::Vec3D viewing_direction = (stood_viewing_direction - stood_position).normalized();
   return viewing_direction;
}


AllegroFlare::Vec3D Camera3D::get_reverse_viewing_direction()
{
   ALLEGRO_TRANSFORM t;
   position_transform(&t);
   AllegroFlare::Vec3D stood_position(0, 0, 0); // TODO: Consider if this needs to be the stepout
   AllegroFlare::Vec3D stood_viewing_direction(0, 0, 1);
   al_transform_coordinates_3d(&t, &stood_position.x, &stood_position.y, &stood_position.z);
   al_transform_coordinates_3d(&t, &stood_viewing_direction.x, &stood_viewing_direction.y, &stood_viewing_direction.z);
   AllegroFlare::Vec3D viewing_direction = (stood_viewing_direction - stood_position).normalized();
   return viewing_direction;
}



/*
void Camera3D::blend_x(AllegroFlare::Camera3D* other, float interpolation)
{
   if (!(other))
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "error: guard \"other\" not met."
      );
   }
   if (!(interpolation <= 1.0f))
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "error: guard \"interpolation < 1.0f\" not met."
      );
   }
   if (!(interpolation >= 0.0f))
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "error: guard \"interpolation >= 0.0f\" not met."
      );
   }

   if (interpolation == 0.0f) return;
   if (interpolation == 1.0f) { *this = *other; return; }

   AllegroFlare::Camera3D &source = *this;
   AllegroFlare::Camera3D &target = *other;
   source.position = (target.position - source.position) * interpolation + source.position;
   source.spin = (target.spin - source.spin) * interpolation + source.spin;
   source.tilt = (target.tilt - source.tilt) * interpolation + source.tilt;
   source.roll = (target.roll - source.roll) * interpolation + source.roll;
   source.stepout = (target.stepout - source.stepout) * interpolation + source.stepout;
   source.zoom = (target.zoom - source.zoom) * interpolation + source.zoom;
   source.near_plane = (target.near_plane - source.near_plane) * interpolation + source.near_plane;
   source.far_plane = (target.far_plane - source.far_plane) * interpolation + source.far_plane;
   return;
}
*/



void Camera3D::blend(AllegroFlare::Camera3D* other, float interpolation)
{
   if (!(other))
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "error: guard \"other\" not met."
      );
   }
   if (!((interpolation >= 0.0f) && (interpolation <= 1.0f)))
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "error: guard \"interpolation >= 0.0f && interpolation <= 1.0f\" not met."
      );
   }

   if (interpolation == 0.0f)
   {
      // No change to 'this' camera
      return;
   }

   if (interpolation == 1.0f)
   {
      // 'this' camera adopts all of 'other's values,
      // but 'this' camera RETAINS its own unit preferences.
      // Non-rotation properties are copied directly:
      this->position = other->position;
      this->stepout = other->stepout;
      this->zoom = other->zoom;
      this->near_plane = other->near_plane;
      this->far_plane = other->far_plane;
      this->shift = other->shift;

      // Rotational properties: assign 'other's value, converting to 'this's native unit system.
      // 'this' camera's *_in_unit_values flags remain UNCHANGED.
      this->spin = convert_to_match_system(
         other->spin,
         other->spin_in_unit_values,
         this->spin_in_unit_values // 'this' camera's original unit preference for spin
      );
      this->tilt = convert_to_match_system(
         other->tilt,
         other->tilt_in_unit_values,
         this->tilt_in_unit_values // 'this' camera's original unit preference for tilt
      );
      this->roll = convert_to_match_system(
         other->roll,
         other->roll_in_unit_values,
         this->roll_in_unit_values // 'this' camera's original unit preference for roll
      );
      return;
   }

   // Interpolation for 0 < interpolation < 1
   // Non-rotation properties:
   this->position = (other->position - this->position) * interpolation + this->position;
   this->stepout = (other->stepout - this->stepout) * interpolation + this->stepout;
   this->zoom = (other->zoom - this->zoom) * interpolation + this->zoom;
   this->near_plane = (other->near_plane - this->near_plane) * interpolation + this->near_plane;
   this->far_plane = (other->far_plane - this->far_plane) * interpolation + this->far_plane;
   this->shift = (other->shift - this->shift) * interpolation + this->shift;

   // Rotational properties:
   // Convert 'other's rotation to 'this' camera's native unit system, then interpolate.
   // 'this' camera's *_in_unit_values flags remain UNCHANGED.
   float other_spin_converted = convert_to_match_system(
      other->spin, other->spin_in_unit_values, this->spin_in_unit_values
   );
   this->spin = (other_spin_converted - this->spin) * interpolation + this->spin;

   float other_tilt_converted = convert_to_match_system(
      other->tilt, other->tilt_in_unit_values, this->tilt_in_unit_values
   );
   this->tilt = (other_tilt_converted - this->tilt) * interpolation + this->tilt;

   float other_roll_converted = convert_to_match_system(
      other->roll, other->roll_in_unit_values, this->roll_in_unit_values
   );
   this->roll = (other_roll_converted - this->roll) * interpolation + this->roll;
}



void Camera3D::use_unit_values()
{
   spin_in_unit_values = true;
   tilt_in_unit_values = true;
   roll_in_unit_values = true;
}



void Camera3D::use_radian_values()
{
   spin_in_unit_values = false;
   tilt_in_unit_values = false;
   roll_in_unit_values = false;
}



} // namespace AllegroFlare


