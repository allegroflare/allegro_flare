#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <vector>


namespace AllegroFlare
{
   class InputDevicesList
   {
   private:
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> devices;

   protected:


   public:
      InputDevicesList();
      ~InputDevicesList();

      void initialize();
      int count_num_keyboard_devices();
      int count_num_joystick_devices();
      void handle_reconfigured_joystick();
      int num_known_devices();
   };
}



