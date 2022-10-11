

#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin)
   : AllegroFlare::Screens::Base("Prototypes::TileDrive::Screen")
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , tile_drive()
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* Screen::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Screen::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::SampleBin* Screen::get_sample_bin() const
{
   return sample_bin;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_sample_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->sample_bin = sample_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->font_bin = font_bin;
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   initialized = true;
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_down_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_down_func" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   switch(event->keyboard.keycode)
   {
     case ALLEGRO_KEY_UP:
       tile_drive.driver_press_accelerator();
       break;

     case ALLEGRO_KEY_DOWN:
       tile_drive.driver_press_break();
       break;

     case ALLEGRO_KEY_RIGHT:
       tile_drive.driver_turn_right();
       break;

     case ALLEGRO_KEY_LEFT:
       tile_drive.driver_turn_left();
       break;

     case ALLEGRO_KEY_R:
       tile_drive.reset();
       break;
   }
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_up_func" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "Screen" << "::" << "key_up_func" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
        tile_drive.driver_unpress_accelerator();
      break;

      case ALLEGRO_KEY_DOWN:
        tile_drive.driver_unpress_break();
      break;

      case ALLEGRO_KEY_RIGHT:
        tile_drive.driver_turn_none();
      break;

      case ALLEGRO_KEY_LEFT:
         tile_drive.driver_turn_none();
      break;
   }
   return;
}


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


