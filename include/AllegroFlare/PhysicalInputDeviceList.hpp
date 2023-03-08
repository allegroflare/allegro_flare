#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <vector>


namespace AllegroFlare
{
   class PhysicalInputDeviceList
   {
   private:
      std::vector<AllegroFlare::PhysicalInputDevices::Base*> devices;

   protected:


   public:
      PhysicalInputDeviceList();
      ~PhysicalInputDeviceList();

      void initialize();
      void handle_reconfigured_joystick();
      int num_known_devices();
   };
}



