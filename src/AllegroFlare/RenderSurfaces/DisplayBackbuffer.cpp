

#include <AllegroFlare/RenderSurfaces/DisplayBackbuffer.hpp>

#include <AllegroFlare/Color.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace RenderSurfaces
{


DisplayBackbuffer::DisplayBackbuffer(ALLEGRO_DISPLAY* display)
   : AllegroFlare::RenderSurfaces::Base(AllegroFlare::RenderSurfaces::DisplayBackbuffer::TYPE)
   , display(display)
   , display_backbuffer(nullptr)
   , initialized(false)
{
}


DisplayBackbuffer::~DisplayBackbuffer()
{
}


ALLEGRO_DISPLAY* DisplayBackbuffer::get_display() const
{
   return display;
}


ALLEGRO_BITMAP* DisplayBackbuffer::get_display_backbuffer() const
{
   return display_backbuffer;
}


void DisplayBackbuffer::set_display(ALLEGRO_DISPLAY* display)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_display]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_display]: error: guard \"(!initialized)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_display]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_display]: error: guard \"display\" not met");
   }
   this->display = display;
   return;
}

void DisplayBackbuffer::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::initialize]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::initialize]: error: guard \"display\" not met");
   }
   display_backbuffer = al_get_backbuffer(display);
   initialized = true;
   return;
}

bool DisplayBackbuffer::set_as_target()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_as_target]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::set_as_target]: error: guard \"initialized\" not met");
   }
   al_set_target_bitmap(display_backbuffer);
   return true;
}

void DisplayBackbuffer::clear_surface()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::clear_surface]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::clear_surface]: error: guard \"initialized\" not met");
   }
   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   al_clear_depth_buffer(1); // This clears on the display, but not necessarily the bitmap?
                             // TODO: Ask if bitmaps can have their depth buffer cleared
}

ALLEGRO_BITMAP* DisplayBackbuffer::obtain_surface()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::obtain_surface]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::obtain_surface]: error: guard \"initialized\" not met");
   }
   return display_backbuffer;
}

int DisplayBackbuffer::get_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::get_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::get_width]: error: guard \"initialized\" not met");
   }
   return al_get_bitmap_width(display_backbuffer);
}

int DisplayBackbuffer::get_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbuffer::get_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbuffer::get_height]: error: guard \"initialized\" not met");
   }
   return al_get_bitmap_height(display_backbuffer);
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


