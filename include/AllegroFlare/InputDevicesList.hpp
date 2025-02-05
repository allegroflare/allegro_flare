#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   class InputDevicesList
   {
   private:
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> devices;
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> first_time_connected_joysticks_after_reconfiguration;
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> previously_known_joysticks_connected_after_reconfiguration;
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> previously_known_joysticks_disconnected_after_reconfiguration;
      float updated_at;
      AllegroFlare::PhysicalInputDevices::Joysticks::Base* find_joystick_device_by_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);
      bool joystick_device_exists_with_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);

   protected:


   public:
      InputDevicesList();
      ~InputDevicesList();

      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_first_time_connected_joysticks_after_reconfiguration() const;
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_previously_known_joysticks_connected_after_reconfiguration() const;
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_previously_known_joysticks_disconnected_after_reconfiguration() const;
      float get_updated_at() const;
      void initialize();
      int num_devices();
      int num_keyboard_devices();
      int num_joystick_devices();
      int num_connected_devices();
      int num_disconnected_devices();
      bool all_devices_are_connected();
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_connected_joysticks();
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_disconnected_joysticks();
      int num_connected_joysticks();
      int num_joysticks_connected_after_last_reconfiguration();
      int num_joysticks_disconnected_after_last_reconfiguration();
      void handle_reconfigured_joystick();
   };
}



