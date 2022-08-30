

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
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/EventNames.hpp>
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


bool EventEmitter::get_initialized() const
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

void EventEmitter::emit_event(uint32_t type, intptr_t data1, intptr_t data2, intptr_t data3, intptr_t data4)
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

void EventEmitter::emit_switch_screen_event(std::string screen_identifier_to_switch_to)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "EventEmitter" << "::" << "emit_switch_screen_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: consider "disable screen", "enable screen", "shutdown screen", etc...
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(screen_identifier_to_switch_to));
   emit_event(ALLEGRO_FLARE_EVENT_SWITCH_SCREEN, data_to_pass);
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

void EventEmitter::emit_show_input_hints_bar_event()
{
   emit_event(ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR);
}

void EventEmitter::emit_hide_input_hints_bar_event()
{
   emit_event(ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR);
}

void EventEmitter::emit_set_input_hints_bar_event(std::vector<std::string> tokens)
{
   intptr_t data_to_pass = (intptr_t)(void *)(new std::vector<std::string>(tokens));
   emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR, data_to_pass);
}

void EventEmitter::emit_set_input_hints_bar_opacity_event(float opacity)
{
   intptr_t data_to_pass = (intptr_t)(void *)(new float(opacity));
   emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_OPACITY, data_to_pass);
}

void EventEmitter::emit_post_unlocked_achievement_notification_event(std::string achievement_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "EventEmitter" << "::" << "emit_post_unlocked_achievement_notification_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(achievement_name));
   emit_event(ALLEGRO_FLARE_EVENT_POST_ACHIEVEMENT_UNLOCKED_NOTIFICATION, data_to_pass);
}

void EventEmitter::emit_play_sound_effect_event(std::string sound_effect_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "EventEmitter" << "::" << "emit_play_sound_effect_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(sound_effect_identifier));
   emit_event(ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT, data_to_pass);
   return;
}

void EventEmitter::emit_play_music_track_event(std::string music_track_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "EventEmitter" << "::" << "emit_play_music_track_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::string *data_to_pass = new std::string(music_track_identifier);
   emit_event(ALLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK, (intptr_t)data_to_pass);
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

void EventEmitter::emit_game_event(AllegroFlare::GameEvent game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "EventEmitter" << "::" << "emit_game_event" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::GameEvent *game_event_copy = new AllegroFlare::GameEvent(game_event);
   emit_event(ALLEGRO_FLARE_EVENT_GAME_EVENT, (intptr_t)game_event_copy);
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


