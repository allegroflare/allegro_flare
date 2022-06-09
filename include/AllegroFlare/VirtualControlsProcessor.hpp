#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <allegro5/allegro.h>
#include <map>


namespace AllegroFlare
{
   class VirtualControlsProcessor
   {
   private:
      AllegroFlare::EventEmitter* event_emitter;
      std::map<int, int> keyboard_button_map;
      std::map<int, int> joystick_button_map;
      bool initialized;

   public:
      VirtualControlsProcessor(AllegroFlare::EventEmitter* event_emitter=nullptr);
      ~VirtualControlsProcessor();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      std::map<int, int> get_keyboard_button_map();
      std::map<int, int> get_joystick_button_map();
      bool get_initialized();
      void initialize();
      std::map<int, int> build_sensible_joystick_button_map();
      std::map<int, int> build_sensible_keyboard_button_map();
      void handle_raw_keyboard_key_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_keyboard_key_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_axis_change_event(ALLEGRO_EVENT* event=nullptr);
      int get_joystick_mapped_virtual_button(int native_button_num=-1);
      int get_keyboard_mapped_virtual_button(int native_key_num=-1);
      void emit_virtual_controls_button_up_event(int virtual_button_num=0);
      void emit_virtual_controls_button_down_event(int virtual_button_num=0);
      void emit_virtual_controls_axis_change_event(int stick=0, int axis=0, float position=0.0f);
   };
}



