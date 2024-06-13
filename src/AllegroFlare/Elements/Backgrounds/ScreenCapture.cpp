

#include <AllegroFlare/Elements/Backgrounds/ScreenCapture.hpp>

#include <AllegroFlare/ScreenCapture.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


ScreenCapture::ScreenCapture()
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::ScreenCapture::TYPE)
   , inv_scale(DEFAULT_INV_SCALE)
   , capture(nullptr)
   , initialized(false)
{
}


ScreenCapture::~ScreenCapture()
{
}


int ScreenCapture::get_inv_scale() const
{
   return inv_scale;
}


void ScreenCapture::set_inv_scale(int inv_scale)
{
   if (!((inv_scale >= 1)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::ScreenCapture::set_inv_scale]: error: guard \"(inv_scale >= 1)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::ScreenCapture::set_inv_scale]: error: guard \"(inv_scale >= 1)\" not met");
   }
   if (!((inv_scale <= 20)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::ScreenCapture::set_inv_scale]: error: guard \"(inv_scale <= 20)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::ScreenCapture::set_inv_scale]: error: guard \"(inv_scale <= 20)\" not met");
   }
   this->inv_scale = inv_scale;
   if (initialized) refresh_capture();
   return;
}

void ScreenCapture::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::ScreenCapture::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::ScreenCapture::initialize]: error: guard \"(!initialized)\" not met");
   }
   refresh_capture();
   initialized = true;
   return;
}

void ScreenCapture::destroy()
{
   if (capture) al_destroy_bitmap(capture);
   return;
}

void ScreenCapture::refresh_capture()
{
   if (capture) al_destroy_bitmap(capture);
   capture = AllegroFlare::ScreenCapture::create_backbuffer_capture_as_scaled_bitmap(
      1920/inv_scale,
      1080/inv_scale
   );
   return;
}

void ScreenCapture::activate()
{
   refresh_capture();
   return;
}

void ScreenCapture::render()
{
   if (capture)
   {
      al_draw_scaled_bitmap(
         capture,
         0,
         0,
         al_get_bitmap_width(capture),
         al_get_bitmap_height(capture),
         0,
         0,
         1920,
         1080,
         0
      );
   }
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


