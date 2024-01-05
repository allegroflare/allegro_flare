#pragma once


#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/RouteEventDatas/Base.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class EventEmitter
   {
   private:
      ALLEGRO_EVENT_SOURCE event_source;
      bool initialized;

   protected:


   public:
      EventEmitter();
      ~EventEmitter();

      bool get_initialized() const;
      ALLEGRO_EVENT_SOURCE &get_event_source_ref();
      void initialize();
      void emit_event(uint32_t type=0, intptr_t data1=0, intptr_t data2=0, intptr_t data3=0, intptr_t data4=0);
      void emit_router_event(uint32_t router_event=0, AllegroFlare::RouteEventDatas::Base* route_event_data=nullptr, float time_now=0.0f);
      void emit_dialog_open_event(std::string dialog_node_name_to_open="[unset-dialog_node_name_to_open]");
      void emit_screen_activated_event(std::string screen_identifier="[unset-screen_identifier]");
      void emit_activate_dialog_node_by_name_event(std::string dialog_node_name_to_activate="[unset-dialog_node_name_to_activate]");
      void emit_load_dialog_file(std::string dialog_yaml_filename_to_load="[unset-dialog_yaml_filename_to_load]");
      static void destroy_dialog_open_event_data(ALLEGRO_USER_EVENT* user_event=nullptr);
      void emit_dialog_advance_event();
      void emit_dialog_close_event();
      void emit_dialog_switched_in_event();
      void emit_dialog_switched_out_event();
      void emit_switch_screen_event(std::string screen_identifier_to_switch_to=0);
      void emit_exit_game_event();
      void emit_show_input_hints_bar_event();
      void emit_hide_input_hints_bar_event();
      void emit_set_input_hints_bar_event(std::vector<std::string> tokens={});
      void emit_set_input_hints_bar_text_opacity_event(float opacity=1.0f);
      void emit_set_input_hints_bar_backfill_opacity_event(float opacity=0.35f);
      void emit_set_input_hints_bar_height_event(float height=60.0f);
      void emit_set_shader_target_for_hotloading_event(AllegroFlare::Shaders::Base* shader=nullptr);
      void emit_poll_hotload_shader_source_for_change_event();
      void emit_hotload_shader_source_event(std::string vertex_shader_source="[unset-vertex_shader_source]", std::string fragment_shader_source="[unset-fragment_shader_source]", AllegroFlare::Shaders::Base* shader=nullptr);
      void emit_unlock_achievement_event(std::string achievement_name="[unset-achievement_name]");
      void emit_achievement_unlocked_game_event(std::string achievement_name="[unset-achievement_name]");
      void emit_post_unlocked_achievement_notification_event(std::string achievement_name="[unset-achievement_name]");
      void emit_play_sound_effect_event(std::string sound_effect_identifier="[unset-sound-effect-identifier]");
      void emit_play_music_track_event(std::string music_track_identifier="[unset-music-track-identifier]");
      void emit_stop_all_music_tracks_event();
      void emit_game_event(AllegroFlare::GameEvent game_event={});
      void emit_offset_primary_timer_event(int microseconds=(16667 / 10));
      void TODO();
   };
}



