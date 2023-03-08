

#include <AllegroFlare/PhysicalInputDeviceList.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


PhysicalInputDeviceList::PhysicalInputDeviceList()
   : devices({})
{
}


PhysicalInputDeviceList::~PhysicalInputDeviceList()
{
}


void PhysicalInputDeviceList::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PhysicalInputDeviceList::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PhysicalInputDeviceList::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   return;
}


} // namespace AllegroFlare


