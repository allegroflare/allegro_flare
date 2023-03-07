#pragma once


#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMapping.hpp>


namespace AllegroFlare
{
   class PhysicalInputDeviceToVirtualControllerMappingFactory
   {
   private:

   protected:


   public:
      PhysicalInputDeviceToVirtualControllerMappingFactory();
      ~PhysicalInputDeviceToVirtualControllerMappingFactory();

      AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping create_single_player_keyboard_mapping_from_scratch();
   };
}



