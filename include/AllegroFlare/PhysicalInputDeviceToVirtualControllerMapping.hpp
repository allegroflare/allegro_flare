#pragma once


#include <AllegroFlare/PhysicalInputDevices/Base.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <cstdint>
#include <map>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   class PhysicalInputDeviceToVirtualControllerMapping
   {
   private:
      AllegroFlare::PhysicalInputDevices::Base* physical_input_device;
      AllegroFlare::VirtualControllers::Base* virtual_controller;
      std::map<int, int> mapping;

   protected:


   public:
      PhysicalInputDeviceToVirtualControllerMapping();
      ~PhysicalInputDeviceToVirtualControllerMapping();

      void set_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device);
      void set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller);
      AllegroFlare::PhysicalInputDevices::Base* get_physical_input_device() const;
      AllegroFlare::VirtualControllers::Base* get_virtual_controller() const;
      std::map<int, int> get_mapping() const;
      void set_multiple_mappings(std::vector<std::pair<int, int>> mappings={});
      void set_mapping(uint32_t physical_input_button_id=0, uint32_t virtual_input_button_id=0);
      bool mapping_exists_on_physical_device_button(uint32_t physical_input_button_id=0);
      bool mapping_exists_on_virtual_controller_button(uint32_t virtual_controller_button_id=0);
   };
}



