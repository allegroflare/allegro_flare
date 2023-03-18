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
      float updated_at;
      AllegroFlare::PhysicalInputDevices::Joysticks::Base* find_joystick_device_by_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);
      bool joystick_device_exists_with_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);

   protected:


   public:
      InputDevicesList();
      ~InputDevicesList();

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
      void handle_reconfigured_joystick();
   };
}



