

#include <AllegroFlare/EventEmitter.hpp>

#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/GameEventDatas/AchievementUnlocked.hpp>
#include <AllegroFlare/GameEventDatas/ScreenActivated.hpp>
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
   throw std::runtime_error("AllegroFlare::EventEmitter::emit_dialog_open_event: deprecation error: Using "
         "ALLEGRO_FLARE_EVENT_DIALOG_OPEN in this way is depreciated, update to ALLEGRO_FLARE_EVENT_DIALOG"
      );

   // TODO: Add test for this emission
   // TODO: Find location to destroy this data after use and destroy it, Use "destroy_dialog_open_event_data"
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(dialog_node_name_to_open));
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_OPEN, data_to_pass);
   return;
}

void EventEmitter::emit_screen_activated_event(std::string screen_identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_screen_activated_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_screen_activated_event: error: guard \"initialized\" not met");
   }
   emit_game_event(AllegroFlare::GameEvent(
         AllegroFlare::GameEventDatas::ScreenActivated::NAME,
         new AllegroFlare::GameEventDatas::ScreenActivated(screen_identifier)
      ));
   return;
}

void EventEmitter::emit_activate_dialog_node_by_name_event(std::string dialog_node_name_to_activate)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_activate_dialog_node_by_name_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_activate_dialog_node_by_name_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   // TODO: Find location to destroy this data after use and destroy it, Use "destroy_dialog_open_event_data"
   //intptr_t data_to_pass = (intptr_t)(void *)(new std::string(dialog_node_name_to_open));
   intptr_t data_to_pass = (intptr_t)(void *)(
      // TODO: Rename this SpawnDialogByName event should be renamed to ActivateDialogNodeByName
      new AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName(dialog_node_name_to_activate)
   );
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG, data_to_pass);
   return;
}

void EventEmitter::destroy_dialog_open_event_data(ALLEGRO_USER_EVENT* user_event)
{
   if (!(user_event))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::destroy_dialog_open_event_data]: error: guard \"user_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::destroy_dialog_open_event_data: error: guard \"user_event\" not met");
   }
   std::string *data = (std::string *)(user_event->data1);
   delete data;
   return;
}

void EventEmitter::emit_dialog_advance_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_advance_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_advance_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_ADVANCE);
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

void EventEmitter::emit_dialog_switch_in_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_switch_in_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_switch_in_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_IN);
   return;
}

void EventEmitter::emit_dialog_switch_out_event()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_dialog_switch_out_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_dialog_switch_out_event: error: guard \"initialized\" not met");
   }
   // TODO: Add test for this emission
   emit_event(ALLEGRO_FLARE_EVENT_DIALOG_SWITCH_OUT);
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

void EventEmitter::emit_unlock_achievement_event(std::string achievement_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_unlock_achievement_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_unlock_achievement_event: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   intptr_t data_to_pass = (intptr_t)(void *)(new std::string(achievement_name));
   emit_event(ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT, data_to_pass);
}

void EventEmitter::emit_achievement_unlocked_game_event(std::string achievement_name)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[EventEmitter::emit_achievement_unlocked_game_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EventEmitter::emit_achievement_unlocked_game_event: error: guard \"initialized\" not met");
   }
   // NOTE: This event is used by the framework after an achievement successfully becomes unlocked. It's useful
   // for framework users who wish to perform some consequential action in their game after an achievement becomes
   // unlocked, such as save the achievement in the gamer's GameProgressAndStateInfos
   // TODO: Test this
   emit_game_event(
      AllegroFlare::GameEvent(
         AllegroFlare::GameEventDatas::AchievementUnlocked::NAME,
         new AllegroFlare::GameEventDatas::AchievementUnlocked(achievement_name)
      )
   );
   return;
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


