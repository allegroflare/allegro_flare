#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   class EventEmitter
   {
   private:
      ALLEGRO_EVENT_SOURCE event_source;
      bool initialized;

   public:
      EventEmitter();
      ~EventEmitter();

      bool get_initialized();
      ALLEGRO_EVENT_SOURCE &get_event_source_ref();
      void initialize();
      void emit_event(unsigned int type=0, intptr_t data1=0, intptr_t data2=0, intptr_t data3=0, intptr_t data4=0);
      void emit_screen_switch_event(std::string screen_identifier_to_switch_to=0);
      void emit_exit_game_event();
      void emit_play_sound_effect_event(std::string sound_effect_identifier="[unset-sound-effect-identifier]");
      void emit_play_music_track_event(std::string music_track_identifier="[unset-music-track-identifier]");
      void emit_virtual_controls_button_up_event(int virtual_button_num=0);
      void emit_virtual_controls_button_down_event(int virtual_button_num=0);
      void emit_virtual_controls_axis_change_event(int stick=0, int axis=0, float position=0.0f);
      void TODO();
   };
}



