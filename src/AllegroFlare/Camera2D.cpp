

#include <AllegroFlare/Camera2D.hpp>

#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Camera2D::Camera2D()
   : AllegroFlare::Placement2D()
   , zoom({1.0f, 1.0f})
   , width_num_units(DEFAULT_WIDTH_NUM_UNITS)
   , height_num_units(DEFAULT_HEIGHT_NUM_UNITS)
{
}


Camera2D::~Camera2D()
{
}


void Camera2D::set_width_num_units(int width_num_units)
{
   this->width_num_units = width_num_units;
}


void Camera2D::set_height_num_units(int height_num_units)
{
   this->height_num_units = height_num_units;
}


AllegroFlare::Vec2D Camera2D::get_zoom() const
{
   return zoom;
}


int Camera2D::get_width_num_units() const
{
   return width_num_units;
}


int Camera2D::get_height_num_units() const
{
   return height_num_units;
}


void Camera2D::set_zoom(AllegroFlare::Vec2D zoom)
{
   scale = AllegroFlare::vec2d(1.0 / zoom.x, 1.0 / zoom.y);
   this->zoom = zoom;
   return;
}

AllegroFlare::Vec2D Camera2D::get_inv_zoom()
{
   // TODO: rename this function and the zoom property
   return AllegroFlare::vec2d(1.0 / zoom.x, 1.0 / zoom.y);
}

void Camera2D::refresh_zoom_from_scale()
{
   this->zoom = AllegroFlare::vec2d(1.0 / scale.x, 1.0 / scale.y);
   return;
}

void Camera2D::setup_dimensional_projection(ALLEGRO_BITMAP* bitmap)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Camera2D::setup_dimensional_projection]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Camera2D::setup_dimensional_projection: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[Camera2D::setup_dimensional_projection]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Camera2D::setup_dimensional_projection: error: guard \"bitmap\" not met");
   }
   // The goal here is to setup a projection transform that behaves as if normal 2D pixels were drawn for z=0
   // (i.e. as with the normal orthographic transform set up by Allegro), but allows some perspective effects for
   // rotating widgets around the X and Y axes.

   //float w = al_get_display_width(al_get_current_display()), h = al_get_display_height(al_get_current_display());
   float w = width_num_units, h = height_num_units;
   float fov_angle = 90.0;
   float fov = tan(fov_angle * ALLEGRO_PI / 180.0 / 2.0);

   // That is the z near plane where we need to draw everything before the perspective transform so that it ends up
   // as 1:1 at pixel-coordingates.
   float z_near = w / 2 * fov;

   // If we really drew at depth of z_near, everything closer to the camera would be z-clipped.
   // This would be a problem for rotations around the x and y axis.
   // Therefore, to avoid z-clipping, we need to move everything further away from the camera before the perspective
   // transform is applied.
   // This is achieved by an additional view matrix which is composed with the perspective transform so that the view
   // transformation happens first.
   const float Z_DIST_FACTOR = 1.1; // larger number makes a deeper distance effect

   ALLEGRO_TRANSFORM perspective;
   al_identity_transform(&perspective);
   // FIXME: Does factor 2 for "far" make sense?
   al_perspective_transform(&perspective, -w / 2, -h / 2, z_near, w / 2, h / 2, z_near * Z_DIST_FACTOR * 2);

   ALLEGRO_TRANSFORM view;
   al_identity_transform(&view);
   // We make up for the perspective correction due to z-translation by scaling everything.
   al_scale_transform(&view, Z_DIST_FACTOR, Z_DIST_FACTOR);
   // Move away from the camera (and center).
   al_translate_transform_3d(&view, -w / 2 * Z_DIST_FACTOR, -h / 2 * Z_DIST_FACTOR, -z_near * Z_DIST_FACTOR);

   al_compose_transform(&view, &perspective);

   ALLEGRO_STATE previous_bitmap_target_state;
   al_store_state(&previous_bitmap_target_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(bitmap);

   //al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   //al_clear_depth_buffer(1);

   al_use_projection_transform(&view);
   al_restore_state(&previous_bitmap_target_state);
   return;
}

void Camera2D::blend_with_other_camera(AllegroFlare::Camera2D* camera_b, float blend_factor)
{
   if (!(camera_b))
   {
      std::stringstream error_message;
      error_message << "[Camera2D::blend_with_other_camera]: error: guard \"camera_b\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Camera2D::blend_with_other_camera: error: guard \"camera_b\" not met");
   }
   // TODO: Improve tests on this
   blend(*camera_b, blend_factor);
   refresh_zoom_from_scale();
   return;
}


} // namespace AllegroFlare


