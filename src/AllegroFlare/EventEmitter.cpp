

#include <AllegroFlare/EventEmitter.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
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


EventEmitter::EventEmitter()
   : event_source()
   , initialized(false)
{
}


EventEmitter::~EventEmitter()
{
}


bool EventEmitter::get_initialized()
{
   return initialized;
}


ALLEGRO_EVENT_SOURCE &EventEmitter::get_event_source_ref()
{
   return event_source;
}


void EventEmitter::initialize()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((!get_initialized())))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
         throw std::runtime_error(error_message.str());
      }
   al_init_user_event_source(&event_source);
   initialized = true;
   return;
}

void EventEmitter::emit_event(unsigned int type, intptr_t data1, intptr_t data2, intptr_t data3, intptr_t data4)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_EVENT event;
   event.user.type = type; //SCREEN_MANAGER_SWITCH_SCREEN_EVENT;
   event.user.data1 = data1; //SCREEN_TITLE_SCREEN;
   event.user.data2 = data2;
   event.user.data3 = data3;
   event.user.data4 = data4;
   al_emit_user_event(&event_source, &event, NULL);
   return;
}

void EventEmitter::emit_screen_switch_event(std::string screen_identifier_to_switch_to)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_screen_switch_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO: implement this:
   // std::string *data_to_pass = new std::string(screen_identifier_to_switch_to);
   //emit_event(SCREEN_MANAGER_SWITCH_SCREEN_EVENT, data_to_pass);
   return;
}

void EventEmitter::emit_exit_game_event()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_exit_game_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   emit_event(ALLEGRO_FLARE_EVENT_EXIT_GAME);
   return;
}

void EventEmitter::emit_virtual_controls_button_up_event(int virtual_button_num)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_virtual_controls_button_up_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   emit_event(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP, virtual_button_num);
   return;
}

void EventEmitter::emit_virtual_controls_button_down_event(int virtual_button_num)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_virtual_controls_button_down_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   emit_event(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN, virtual_button_num);
   return;
}

void EventEmitter::emit_virtual_controls_axis_change_event(int stick, int axis, float position)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "EventEmitter" << "::" << "emit_virtual_controls_axis_change_event" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO: not implemented (not tested!)
   emit_event(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE, stick, axis, (int)(position * 255));
   return;
}

void EventEmitter::TODO()
{
   // note this class is based on DragonWrath/UserEventEmitter
   return;
}
} // namespace AllegroFlare


