

#include <AllegroFlare/EventEmitter.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[EventEmitter::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::initialize: error: guard \"(!get_initialized())\" not met");
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
      error_message << "[EventEmitter::emit_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_event: error: guard \"initialized\" not met");
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

void EventEmitter::emit_router_event(uint32_t router_event, AllegroFlare::RouteEventDatas::Base* route_event_data, float time_now)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_router_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_router_event: error: guard \"initialized\" not met");
   }
   float *time_now_ptr = new float(time_now);
   emit_event(ALLEGRO_FLARE_EVENT_ROUTER, router_event, (intptr_t)route_event_data, (intptr_t)time_now_ptr);
   return;
}

void EventEmitter::emit_dialog_open_event(std::string dialog_node_name_to_open)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_open_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_open_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(dialog_node_name_to_open));
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_OPEN, data_to_pass);
   return;
}

void EventEmitter::emit_dialog_close_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_close_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_close_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_CLOSE);
   return;
}

void EventEmitter::emit_dialog_next_page()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_next_page]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_next_page: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_NEXT_PAGE);
   return;
}

void EventEmitter::emit_switch_screen_event(std::string screen_identifier_to_switch_to)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_switch_screen_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_switch_screen_event: error: guard \"initialized\" not met");
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
      error_message << "[EventEmitter::emit_exit_game_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_exit_game_event: error: guard \"initialized\" not met");
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

void EventEmitter::emit_set_input_hints_bar_text_opacity_event(float opacity)
{
   intptr_t data_to_pass = (intptr_t)(void *)(new float(opacity));
   emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_TEXT_OPACITY, data_to_pass);
}

void EventEmitter::emit_set_input_hints_bar_backfill_opacity_event(float opacity)
{
   // TODO: use a shared constant for the default value
   intptr_t data_to_pass = (intptr_t)(void *)(new float(opacity));
   emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_BACKFILL_OPACITY, data_to_pass);
}

void EventEmitter::emit_set_input_hints_bar_height_event(float height)
{
   intptr_t data_to_pass = (intptr_t)(void *)(new float(height));
   emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR_HEIGHT, data_to_pass);
}

void EventEmitter::emit_set_shader_target_for_hotloading_event(AllegroFlare::Shaders::Base* shader)
{
   // TODO: add test for this function
   intptr_t data_to_pass = (intptr_t)(void *)(shader);
   emit_event(ALLEGRO_FLARE_EVENT_SET_SHADER_TARGET_FOR_HOTLOADING, data_to_pass);
}

void EventEmitter::emit_poll_hotload_shader_source_for_change_event()
{
   // TODO: add test for this function
   emit_event(ALLEGRO_FLARE_EVENT_POLL_HOTLOAD_SHADER_SOURCE_FOR_CHANGE);
}

void EventEmitter::emit_hotload_shader_source_event(std::string vertex_shader_source, std::string fragment_shader_source, AllegroFlare::Shaders::Base* shader)
{
   // TODO: add test for this function
   intptr_t vertex_shader_source_data = (intptr_t)(void *)(new std::string(vertex_shader_source));
   intptr_t fragment_shader_source_data = (intptr_t)(void *)(new std::string(fragment_shader_source));
   emit_event(
      ALLEGRO_FLARE_EVENT_HOTLOAD_SHADER_SOURCE,
      vertex_shader_source_data,
      fragment_shader_source_data,
      (intptr_t)shader
   );
}

void EventEmitter::emit_post_unlocked_achievement_notification_event(std::string achievement_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_post_unlocked_achievement_notification_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_post_unlocked_achievement_notification_event: error: guard \"initialized\" not met");
   }
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(achievement_name));
   emit_event(ALLEGRO_FLARE_EVENT_POST_ACHIEVEMENT_UNLOCKED_NOTIFICATION, data_to_pass);
}

void EventEmitter::emit_play_sound_effect_event(std::string sound_effect_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_play_sound_effect_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_play_sound_effect_event: error: guard \"initialized\" not met");
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
      error_message << "[EventEmitter::emit_play_music_track_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_play_music_track_event: error: guard \"initialized\" not met");
   }
   std::string *data_to_pass = new std::string(music_track_identifier);
   emit_event(ALLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK, (intptr_t)data_to_pass);
   return;
}

void EventEmitter::emit_stop_all_music_tracks_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_stop_all_music_tracks_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_stop_all_music_tracks_event: error: guard \"initialized\" not met");
   }
   emit_event(ALLEGRO_FLARE_EVENT_STOP_ALL_MUSIC_TRACKS);
   return;
}

void EventEmitter::emit_game_event(AllegroFlare::GameEvent game_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_game_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_game_event: error: guard \"initialized\" not met");
   }
   AllegroFlare::GameEvent *game_event_copy = new AllegroFlare::GameEvent(game_event);
   emit_event(ALLEGRO_FLARE_EVENT_GAME_EVENT, (intptr_t)game_event_copy);
   return;
}

void EventEmitter::TODO()
{
   // note this class is based on DragonWrath/UserEventEmitter
   return;
}


} // namespace AllegroFlare


