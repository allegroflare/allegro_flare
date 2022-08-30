

#include <AllegroFlare/VirtualControlsProcessor.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/VirtualControls.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{


VirtualControlsProcessor::VirtualControlsProcessor(AllegroFlare::EventEmitter* event_emitter)
   : event_emitter(event_emitter)
   , keyboard_button_map()
   , joystick_button_map()
   , initialized(false)
{
}


VirtualControlsProcessor::~VirtualControlsProcessor()
{
}


void VirtualControlsProcessor::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


std::map<int, std::pair<int, int>> VirtualControlsProcessor::get_keyboard_button_map() const
{
   return keyboard_button_map;
}


std::map<int, int> VirtualControlsProcessor::get_joystick_button_map() const
{
   return joystick_button_map;
}


bool VirtualControlsProcessor::get_initialized() const
{
   return initialized;
}


void VirtualControlsProcessor::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   keyboard_button_map = build_sensible_keyboard_button_map();
   joystick_button_map = build_sensible_joystick_button_map();
   initialized = true;
   return;
}

std::map<int, int> VirtualControlsProcessor::build_sensible_joystick_button_map()
{
   std::map<int, int> result_button_map = {
     { 1, AllegroFlare::VirtualControls::get_BUTTON_A() }, // for x-box controller, but buttons named like SNES layout
     { 0, AllegroFlare::VirtualControls::get_BUTTON_B() },
     { 4, AllegroFlare::VirtualControls::get_BUTTON_X() },
     { 3, AllegroFlare::VirtualControls::get_BUTTON_Y() },

     { 6, AllegroFlare::VirtualControls::get_BUTTON_LEFT_BUMPER() },
     { 7, AllegroFlare::VirtualControls::get_BUTTON_RIGHT_BUMPER() },

     { 11, AllegroFlare::VirtualControls::get_BUTTON_START() },
   };
   return result_button_map;
}

std::map<int, std::pair<int, int>> VirtualControlsProcessor::build_sensible_keyboard_button_map()
{
   static int PLAYER_0 = 0;
          // { keyboard_key, { player_num, virtual_button } }
   std::map<int, std::pair<int, int>> result_button_map = {
     { ALLEGRO_KEY_ENTER, { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_START() } },
     { ALLEGRO_KEY_SPACE, { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_A() } },
     { ALLEGRO_KEY_A,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_A() } },
     { ALLEGRO_KEY_B,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_B() } },
     { ALLEGRO_KEY_X,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_X() } },
     { ALLEGRO_KEY_Y,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_Y() } },
     { ALLEGRO_KEY_UP,    { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_UP() } },
     { ALLEGRO_KEY_DOWN,  { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_DOWN() } },
     { ALLEGRO_KEY_LEFT,  { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_LEFT() } },
     { ALLEGRO_KEY_RIGHT, { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_RIGHT() } },
     { ALLEGRO_KEY_R,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_RIGHT_BUMPER() } },
     { ALLEGRO_KEY_E,     { PLAYER_0, AllegroFlare::VirtualControls::get_BUTTON_LEFT_BUMPER() } },
   };
   return result_button_map;
}

void VirtualControlsProcessor::handle_raw_keyboard_key_down_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_down_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_down_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_down_event" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::pair<int, int> player_num_and_virtual_button =
      get_keyboard_mapped_player_num_and_virtual_button(event->keyboard.keycode);
   if (player_num_and_virtual_button == std::pair<int, int>{-1, -1}) return;
      // ^^ TODO: this behavior should be a little better; Maybe "has_mapping" first

   int player_num = player_num_and_virtual_button.first;
   int virtual_button = player_num_and_virtual_button.second;

   emit_virtual_controls_button_down_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_keyboard_key_up_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_up_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_up_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_keyboard_key_up_event" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::pair<int, int> player_num_and_virtual_button =
      get_keyboard_mapped_player_num_and_virtual_button(event->keyboard.keycode);
   if (player_num_and_virtual_button == std::pair<int, int>{-1, -1}) return;
      // ^^ TODO: this behavior should be a little better; Maybe "has_mapping" first

   int player_num = player_num_and_virtual_button.first;
   int virtual_button = player_num_and_virtual_button.second;

   emit_virtual_controls_button_up_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_button_down_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_down_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_down_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_down_event" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   int virtual_button = get_joystick_mapped_virtual_button(event->joystick.button);
   if (virtual_button == -1) return; // TODO: this behavior should be a little better; Maybe "has_mapping" first
   int player_num = 0; // assume player 0 for now

   emit_virtual_controls_button_down_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_button_up_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_up_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_up_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_button_up_event" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   int virtual_button = get_joystick_mapped_virtual_button(event->joystick.button);
   if (virtual_button == -1) return; // TODO: this behavior should be a little better; Maybe "has_mapping" first
   int player_num = 0; // assume player 0 for now

   emit_virtual_controls_button_up_event(player_num, virtual_button);
   return;
}

void VirtualControlsProcessor::handle_raw_joystick_axis_change_event(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_axis_change_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_axis_change_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "handle_raw_joystick_axis_change_event" << ": error: " << "guard \"event\" not met";
      throw std::runtime_error(error_message.str());
   }
   emit_virtual_controls_axis_change_event(event->joystick.stick, event->joystick.axis, event->joystick.pos);
   return;
}

int VirtualControlsProcessor::get_joystick_mapped_virtual_button(int native_button_num)
{
   bool map_value_exists = joystick_button_map.find(native_button_num) != joystick_button_map.end();
   if (!map_value_exists) return -1;
   int virtual_button = joystick_button_map[native_button_num];
   return virtual_button;
}

std::pair<int, int> VirtualControlsProcessor::get_keyboard_mapped_player_num_and_virtual_button(int native_key_num)
{
   bool map_value_exists = keyboard_button_map.find(native_key_num) != keyboard_button_map.end();
   if (!map_value_exists) return { -1, -1 };

   std::pair<int, int> virtual_player_num_and_virtual_button = keyboard_button_map[native_key_num];
   //int virtual_button = keyboard_button_map[native_key_num].second;

   return virtual_player_num_and_virtual_button;
}

void VirtualControlsProcessor::emit_virtual_controls_button_up_event(int player_num, int virtual_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_button_up_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_button_up_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP,
      player_num,
      virtual_button_num,
      is_repeat
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_button_down_event(int player_num, int virtual_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_button_down_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_button_down_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(
      ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN,
      player_num,
      virtual_button_num,
      is_repeat
   );
   return;
}

void VirtualControlsProcessor::emit_virtual_controls_axis_change_event(int stick, int axis, float position)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_axis_change_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "VirtualControlsProcessor" << "::" << "emit_virtual_controls_axis_change_event" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: consider using non-global event names for these types, or a better design for this scope
   event_emitter->emit_event(ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE, stick, axis, (int)(position * 255));
   return;
}
} // namespace AllegroFlare


