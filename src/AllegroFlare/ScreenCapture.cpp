

#include <AllegroFlare/ScreenCapture.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


ScreenCapture::ScreenCapture()
{
}


ScreenCapture::~ScreenCapture()
{
}


ALLEGRO_BITMAP* ScreenCapture::create_capture()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture" << ": error: " << "guard \"al_get_current_display()\" not met";
      throw std::runtime_error(error_message.str());
   }
   al_flip_display();
   ALLEGRO_BITMAP *captured_screen = al_clone_bitmap(al_get_backbuffer(al_get_current_display()));
   al_flip_display();
   return captured_screen;
}

ALLEGRO_BITMAP* ScreenCapture::create_capture_as_scaled_bitmap(int destination_width, int destination_height)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture_as_scaled_bitmap" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture_as_scaled_bitmap" << ": error: " << "guard \"al_get_current_display()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(destination_width >= 1))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture_as_scaled_bitmap" << ": error: " << "guard \"destination_width >= 1\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(destination_height >= 1))
   {
      std::stringstream error_message;
      error_message << "ScreenCapture" << "::" << "create_capture_as_scaled_bitmap" << ": error: " << "guard \"destination_height >= 1\" not met";
      throw std::runtime_error(error_message.str());
   }
   ALLEGRO_BITMAP *capture = create_capture();
   // TODO: consider new bitmap flags
   // TODO: consider capturing new bitmap flags when storing "previous_target" state
   ALLEGRO_BITMAP *destination = al_create_bitmap(destination_width, destination_height);

   if (!capture || !destination)
   {
      // TODO: throw an error message
   }

   ALLEGRO_STATE previous_target;
   al_store_state(&previous_target, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(destination);
   al_draw_scaled_bitmap(
      capture,
      0,
      0,
      al_get_bitmap_width(capture),
      al_get_bitmap_height(capture),
      0,
      0,
      al_get_bitmap_width(destination),
      al_get_bitmap_height(destination),
      0
   );

   al_restore_state(&previous_target);

   al_destroy_bitmap(capture);
   return destination;
}


} // namespace AllegroFlare


