

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


} // namespace AllegroFlare


