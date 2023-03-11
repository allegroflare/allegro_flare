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
      AllegroFlare::PhysicalInputDevices::Joysticks::Base* find_joystick_device_by_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);
      bool joystick_device_exists_with_al_joystick(ALLEGRO_JOYSTICK* al_joystick=nullptr);

   protected:


   public:
      InputDevicesList();
      ~InputDevicesList();

      void initialize();
      int count_num_keyboard_devices();
      int count_num_joystick_devices();
      int count_num_connected_devices();
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> get_connected_joysticks();
      void handle_reconfigured_joystick();
      int num_known_devices();
   };
}



