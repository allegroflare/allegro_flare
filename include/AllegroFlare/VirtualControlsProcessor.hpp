#pragma once


#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/InputDevicesList.hpp>
#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMapping.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   class VirtualControlsProcessor
   {
   private:
      AllegroFlare::InputDevicesList* input_devices_list;
      AllegroFlare::EventEmitter* event_emitter;
      std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> physical_input_device_to_virtual_control_mappings;
      bool initialized;
      int get_joystick_mapped_virtual_button(int native_button_num=-1);
      AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping* get_keyboard_mapped_physical_input_device_to_virtual_controller_mapping(int al_keyboard_keycode=-1);

   protected:


   public:
      VirtualControlsProcessor(AllegroFlare::InputDevicesList* input_devices_list=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
      ~VirtualControlsProcessor();

      bool get_initialized() const;
      std::vector<AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping> &get_physical_input_device_to_virtual_control_mappings_ref();
      void set_input_devices_list(AllegroFlare::InputDevicesList* input_devices_list=nullptr);
      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
      void initialize();
      void handle_raw_keyboard_key_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_keyboard_key_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_down_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_button_up_event(ALLEGRO_EVENT* event=nullptr);
      void handle_raw_joystick_axis_change_event(ALLEGRO_EVENT* event=nullptr);
      void handle_joystick_device_configuration_change_event(ALLEGRO_EVENT* event=nullptr);
      void emit_virtual_controls_button_up_event(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false);
      void emit_virtual_controls_button_down_event(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false);
      void emit_virtual_controls_axis_change_event(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_stick=0, int virtual_controller_axis=0, float virtual_controller_position=0.0f);
   };
}



