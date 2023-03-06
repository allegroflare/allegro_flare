#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMapping.hpp>
#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class VirtualControlsProcessor
   {
   private:
      AllegroFlare::EventEmitter* event_emitter;
      std::map<AllegroFlare::PhysicalInputDevices::Base*, int> physical_input_devices;
      std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> physical_input_device_to_virtual_control_mappings;
      bool initialized;
      void setup_configuration_of_connected_joystick_devices();
      int get_joystick_mapped_virtual_button(int native_button_num=-1);
      std::pair<int, int> get_keyboard_mapped_player_num_and_virtual_button(int al_keyboard_keycode=-1);

   protected:


   public:
      VirtualControlsProcessor(AllegroFlare::EventEmitter* event_emitter=nullptr);
      ~VirtualControlsProcessor();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      bool get_initialized() const;
      std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> &get_physical_input_device_to_virtual_control_mappings_ref();
      void initialize();
      int infer_num_physical_input_devices();
      int infer_num_physical_input_devices_connected();
      int find_player_num_from_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);
      void handle_raw_keyboard_key_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_keyboard_key_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_axis_change_event(ALLEGRO_EVENT* event=nullptr);
      void handle_joystick_device_configuration_change_event(ALLEGRO_EVENT* event=nullptr);
      void emit_virtual_controls_button_up_event(int player_num=0, int virtual_button_num=0, bool is_repeat=false);
      void emit_virtual_controls_button_down_event(int player_num=0, int virtual_button_num=0, bool is_repeat=false);
      void emit_virtual_controls_axis_change_event(int player_num=0, int stick=0, int axis=0, float position=0.0f);
   };
}



