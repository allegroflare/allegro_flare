

#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Screen::Screen(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::AudioController* audio_controller)
   : AllegroFlare::Screens::Base("Prototypes::FixedRoom2D::Screen")
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , audio_controller(audio_controller)
   , fixed_room_2d({})
   , initialized(false)
{
}


Screen::~Screen()
{
}


AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D &Screen::get_fixed_room_2d_ref()
{
   return fixed_room_2d;
}


void Screen::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(audio_controller))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"audio_controller\" not met";
         throw std::runtime_error(error_message.str());
      }
   fixed_room_2d.set_bitmap_bin(bitmap_bin);
   fixed_room_2d.set_font_bin(font_bin);
   fixed_room_2d.set_event_emitter(event_emitter);
   fixed_room_2d.set_audio_controller(audio_controller);
   fixed_room_2d.initialize();

   fixed_room_2d.load_story_and_start();

   initialized = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "game_event_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(game_event))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "game_event_func" << ": error: " << "guard \"game_event\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (fixed_room_2d.is_subscribed_to_game_event_name(game_event->get_type()))
   {
      fixed_room_2d.process_subscribed_to_game_event(game_event);
   };
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "on_deactivate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   fixed_room_2d.update();
   fixed_room_2d.render();
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "key_char_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   float cursor_speed = 10.0f;
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         fixed_room_2d.move_cursor(0, -cursor_speed);
         fixed_room_2d.move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         fixed_room_2d.move_cursor(0, cursor_speed);
         fixed_room_2d.move_cursor_down();
      break;

      case ALLEGRO_KEY_LEFT:
         fixed_room_2d.move_cursor(-cursor_speed, 0);
         fixed_room_2d.move_cursor_left();
      break;

      case ALLEGRO_KEY_RIGHT:
         fixed_room_2d.move_cursor(cursor_speed, 0);
         fixed_room_2d.move_cursor_right();
      break;

      case ALLEGRO_KEY_ENTER:
         fixed_room_2d.activate_primary_action();
      break;

      case ALLEGRO_KEY_I:
         fixed_room_2d.toggle_inventory();
      break;

      case ALLEGRO_KEY_P:
         event_emitter->emit_game_event(AllegroFlare::GameEvent("pause_game"));
         //fixed_room_2d.pause_game();
      break;

      case ALLEGRO_KEY_U:
         event_emitter->emit_game_event(AllegroFlare::GameEvent("unpause_game"));
         //fixed_room_2d.unpause_game();
      break;
   }
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


