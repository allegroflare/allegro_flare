

#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Prototypes/FixedRoom2D/EventNames.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>
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


void Screen::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Screen" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   fixed_room_2d.set_bitmap_bin(bitmap_bin);
   fixed_room_2d.set_font_bin(font_bin);
   fixed_room_2d.set_event_emitter(event_emitter);
   fixed_room_2d.set_audio_controller(audio_controller);
   fixed_room_2d.initialize();
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
   if (game_event->is_type(AllegroFlare::Prototypes::FixedRoom2D::EventNames::INTERACTION_EVENT_NAME))
   {
      AllegroFlare::GameEventDatas::Base *data = game_event->get_data();
      if (data && data->get_type() == "InteractionEventData")
      {
         // cast data to InteractionEventData
         AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData* interaction_event_data =
             static_cast<AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData*>(game_event->get_data());

         // have room2d process the event
         fixed_room_2d.process_interaction_event(interaction_event_data);
      }
      else
      {
         std::cout << "Odd error" << std::endl;
      }
   }

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
      break;

      case ALLEGRO_KEY_DOWN:
         fixed_room_2d.move_cursor(0, cursor_speed);
      break;

      case ALLEGRO_KEY_LEFT:
         fixed_room_2d.move_cursor(-cursor_speed, 0);
      break;

      case ALLEGRO_KEY_RIGHT:
         fixed_room_2d.move_cursor(cursor_speed, 0);
      break;

      case ALLEGRO_KEY_ENTER:
         fixed_room_2d.activate_primary_action();
      break;

      case ALLEGRO_KEY_S:
         fixed_room_2d.spawn_dialog_box();
      break;

      case ALLEGRO_KEY_I:
         fixed_room_2d.toggle_inventory();
      break;
   }
   return;
}
} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


