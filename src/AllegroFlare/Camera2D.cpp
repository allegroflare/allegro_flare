

#include <AllegroFlare/Camera2D.hpp>

#include <cmath>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Camera2D::Camera2D()
   : AllegroFlare::Placement2D()
   , zoom(1.0f)
{
}


Camera2D::~Camera2D()
{
}


float Camera2D::get_zoom() const
{
   return zoom;
}


void Camera2D::set_zoom(float zoom)
{
   scale = AllegroFlare::vec2d(1.0 / zoom, 1.0 / zoom);
   return;
}

void Camera2D::setup_dimentional_projection(ALLEGRO_BITMAP* bitmap)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Camera2D" << "::" << "setup_dimentional_projection" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "Camera2D" << "::" << "setup_dimentional_projection" << ": error: " << "guard \"bitmap\" not met";
      throw std::runtime_error(error_message.str());
   }
   // The goal here is to setup a projection transform that behaves as if normal 2D pixels were drawn for z=0
   // (i.e. as with the normal orthographic transform set up by Allegro), but allows some perspective effects for
   // rotating widgets around the X and Y axes.

   //float w = al_get_display_width(al_get_current_display()), h = al_get_display_height(al_get_current_display());
   float w = 1920, h = 1080;
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


} // namespace AllegroFlare


