

#include <AllegroFlare/RenderSurfaces/DisplayBackbufferSubBitmap.hpp>

#include <AllegroFlare/Color.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace RenderSurfaces
{


DisplayBackbufferSubBitmap::DisplayBackbufferSubBitmap(ALLEGRO_DISPLAY* display)
   : AllegroFlare::RenderSurfaces::Base(AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::TYPE)
   , display(display)
   , display_backbuffer_sub_bitmap(nullptr)
   , initialized(false)
{
}


DisplayBackbufferSubBitmap::~DisplayBackbufferSubBitmap()
{
}


ALLEGRO_DISPLAY* DisplayBackbufferSubBitmap::get_display() const
{
   return display;
}


ALLEGRO_BITMAP* DisplayBackbufferSubBitmap::get_display_backbuffer_sub_bitmap() const
{
   return display_backbuffer_sub_bitmap;
}


void DisplayBackbufferSubBitmap::set_display(ALLEGRO_DISPLAY* display)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_display]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_display]: error: guard \"(!initialized)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_display]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_display]: error: guard \"display\" not met");
   }
   this->display = display;
   return;
}

void DisplayBackbufferSubBitmap::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::initialize]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::initialize]: error: guard \"display\" not met");
   }
   ALLEGRO_BITMAP *backbuffer_bitmap = al_get_backbuffer(display);

   display_backbuffer_sub_bitmap = al_create_sub_bitmap(
      backbuffer_bitmap,
      0,
      0,
      al_get_bitmap_width(backbuffer_bitmap),
      al_get_bitmap_height(backbuffer_bitmap)
   );

   if (!display_backbuffer_sub_bitmap)
   {
      std::cout <<
         "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::initialize]: ERROR: "
         "could not create display_backbuffer_sub_bitmap" << std::endl;
   }
   //camera_2d.setup_dimensional_projection(display_backbuffer_sub_bitmap);
                                                               // this should remain the same throughout
                                                               // the whole program and never be modified

   // TODO: Do this in the framework
   //camera_2d.setup_dimensional_projection(backbuffer_bitmap); // this could potentially change depending on the
                                                                // needs of the game, but is setup here as a reasonable
                                                                // default
                                                                // TODO: replace this with display_backbuffer

   //display_backbuffer = al_get_backbuffer(display);
   initialized = true;
   return;
}

bool DisplayBackbufferSubBitmap::set_as_target()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_as_target]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::set_as_target]: error: guard \"initialized\" not met");
   }
   al_set_target_bitmap(display_backbuffer_sub_bitmap);
   return true;
}

void DisplayBackbufferSubBitmap::clear_surface()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::clear_surface]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::clear_surface]: error: guard \"initialized\" not met");
   }
   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   al_clear_depth_buffer(1); // This clears on the display, but not necessarily the bitmap?
                             // TODO: Ask if bitmaps can have their depth buffer cleared
}

ALLEGRO_BITMAP* DisplayBackbufferSubBitmap::obtain_surface()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::obtain_surface]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::obtain_surface]: error: guard \"initialized\" not met");
   }
   return display_backbuffer_sub_bitmap;
}

int DisplayBackbufferSubBitmap::get_width()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::get_width]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::get_width]: error: guard \"initialized\" not met");
   }
   return al_get_bitmap_width(display_backbuffer_sub_bitmap);
}

int DisplayBackbufferSubBitmap::get_height()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::get_height]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::RenderSurfaces::DisplayBackbufferSubBitmap::get_height]: error: guard \"initialized\" not met");
   }
   return al_get_bitmap_height(display_backbuffer_sub_bitmap);
}


} // namespace RenderSurfaces
} // namespace AllegroFlare


