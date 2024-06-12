

#include <AllegroFlare/ScreenCapture.hpp>

#include <iostream>
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


ALLEGRO_BITMAP* ScreenCapture::create_backbuffer_capture()
{
   return create_capture(false);
}

ALLEGRO_BITMAP* ScreenCapture::create_frontbuffer_capture()
{
   return create_capture(true);
}

ALLEGRO_BITMAP* ScreenCapture::create_capture(bool flip_display_for_capture)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture]: error: guard \"al_get_current_display()\" not met");
   }
   if (flip_display_for_capture) al_flip_display();
   ALLEGRO_BITMAP *captured_screen = al_clone_bitmap(al_get_backbuffer(al_get_current_display()));
   if (flip_display_for_capture) al_flip_display();
   return captured_screen;
}

ALLEGRO_BITMAP* ScreenCapture::create_frontbuffer_capture_as_scaled_bitmap(int destination_width, int destination_height)
{
   return create_capture_as_scaled_bitmap(destination_width, destination_height, true);
}

ALLEGRO_BITMAP* ScreenCapture::create_backbuffer_capture_as_scaled_bitmap(int destination_width, int destination_height)
{
   return create_capture_as_scaled_bitmap(destination_width, destination_height, false);
}

ALLEGRO_BITMAP* ScreenCapture::create_capture_as_scaled_bitmap(int destination_width, int destination_height, bool flip_display_for_capture)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"al_get_current_display()\" not met");
   }
   if (!(destination_width >= 1))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"destination_width >= 1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"destination_width >= 1\" not met");
   }
   if (!(destination_height >= 1))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"destination_height >= 1\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap]: error: guard \"destination_height >= 1\" not met");
   }
   ALLEGRO_BITMAP *capture = create_capture(flip_display_for_capture);
   // TODO: consider new bitmap flags
   // TODO: consider capturing new bitmap flags when storing "previous_target" state
   ALLEGRO_BITMAP *destination = al_create_bitmap(destination_width, destination_height);

   if (!capture || !destination)
   {
      std::stringstream error_message;
      error_message << "AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap() error: "
                    << "Either \"capture\" or \"destination\" bitmaps are nullptr. (capture: " << capture << ", "
                    << "destination: " << destination << ").";
      throw std::runtime_error(error_message.str());
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


