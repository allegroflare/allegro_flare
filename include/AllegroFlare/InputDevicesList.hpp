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

      std::vector<AllegroFlare::PhysicalInputDevices::Base*> &get_devices_ref();
      void initialize();
      void handle_reconfigured_joystick();
      int num_known_devices();
   };
}



