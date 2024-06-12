

#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMapping.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


PhysicalInputDeviceToVirtualControllerMapping::PhysicalInputDeviceToVirtualControllerMapping()
   : player(nullptr)
   , physical_input_device(nullptr)
   , virtual_controller(nullptr)
   , mapping({})
{
}


PhysicalInputDeviceToVirtualControllerMapping::~PhysicalInputDeviceToVirtualControllerMapping()
{
}


void PhysicalInputDeviceToVirtualControllerMapping::set_player(AllegroFlare::Player* player)
{
   this->player = player;
}


void PhysicalInputDeviceToVirtualControllerMapping::set_physical_input_device(AllegroFlare::PhysicalInputDevices::Base* physical_input_device)
{
   this->physical_input_device = physical_input_device;
}


void PhysicalInputDeviceToVirtualControllerMapping::set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller)
{
   this->virtual_controller = virtual_controller;
}


AllegroFlare::Player* PhysicalInputDeviceToVirtualControllerMapping::get_player() const
{
   return player;
}


AllegroFlare::PhysicalInputDevices::Base* PhysicalInputDeviceToVirtualControllerMapping::get_physical_input_device() const
{
   return physical_input_device;
}


AllegroFlare::VirtualControllers::Base* PhysicalInputDeviceToVirtualControllerMapping::get_virtual_controller() const
{
   return virtual_controller;
}


std::map<int, int> PhysicalInputDeviceToVirtualControllerMapping::get_mapping() const
{
   return mapping;
}


void PhysicalInputDeviceToVirtualControllerMapping::set_multiple_mappings(std::vector<std::pair<int, int>> mappings)
{
   for (auto &mappings_element : mappings)
   {
      set_mapping(mappings_element.first, mappings_element.second);
   }
   return;
}

void PhysicalInputDeviceToVirtualControllerMapping::set_mapping(uint32_t physical_input_button_id, uint32_t virtual_input_button_id)
{
   mapping[physical_input_button_id] = virtual_input_button_id;
   return;
}

bool PhysicalInputDeviceToVirtualControllerMapping::mapping_exists_on_physical_device_button(uint32_t physical_input_button_id)
{
   return (mapping.count(physical_input_button_id) > 0);
}

bool PhysicalInputDeviceToVirtualControllerMapping::physical_input_device_is_keyboard()
{
   // TODO: add a test for this
   return physical_input_device && physical_input_device->is_keyboard();
}

int PhysicalInputDeviceToVirtualControllerMapping::get_mapping(uint32_t physical_input_button_id)
{
   if (!(mapping_exists_on_physical_device_button(physical_input_button_id)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping::get_mapping]: error: guard \"mapping_exists_on_physical_device_button(physical_input_button_id)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping::get_mapping]: error: guard \"mapping_exists_on_physical_device_button(physical_input_button_id)\" not met");
   }
   // TODO: Add optional throw on guard or ignore
   return mapping[physical_input_button_id];
}

bool PhysicalInputDeviceToVirtualControllerMapping::mapping_exists_on_virtual_controller_button(uint32_t virtual_controller_button_id)
{
   return (mapping.count(virtual_controller_button_id) > 0);
}


} // namespace AllegroFlare


