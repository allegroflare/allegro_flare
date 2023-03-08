

#include <AllegroFlare/InputDevicesList.hpp>

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>
#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


InputDevicesList::InputDevicesList()
   : devices({})
{
}


InputDevicesList::~InputDevicesList()
{
}


void InputDevicesList::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[InputDevicesList::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("InputDevicesList::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   // create a keyboard (if it is installed)
   if (al_is_keyboard_installed())
   {
      AllegroFlare::PhysicalInputDevices::Keyboard *keyboard = new AllegroFlare::PhysicalInputDevices::Keyboard();
      devices.push_back(keyboard);
   }

   // Create joysticks (for any that are connected)
   al_reconfigure_joysticks();
   int num_joysticks = al_get_num_joysticks();
   for (int i=0; i<num_joysticks; i++)
   {
      ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(i);

      // TODO: consider the following data
      //al_get_joystick_active
      //al_get_joystick_name
      //al_get_joystick_stick_name
      //al_get_joystick_axis_name
      //al_get_joystick_button_name
      //al_get_joystick_stick_flags
      //al_get_joystick_num_sticks
      //al_get_joystick_num_axes
      //al_get_joystick_num_buttons
      //al_get_joystick_state

      AllegroFlare::PhysicalInputDevices::Joysticks::Base *joystick =
         new AllegroFlare::PhysicalInputDevices::Joysticks::Base();
      joystick->set_al_joystick(al_joystick);

      devices.push_back(joystick);
   }
   return;
}

int InputDevicesList::count_num_keyboard_devices()
{
   int keyboard_count = 0;
   for (auto &device : devices) { if (device->is_keyboard()) keyboard_count++; }
   return keyboard_count;
}

int InputDevicesList::count_num_joystick_devices()
{
   int joystick_count = 0;
   for (auto &device : devices) { if (device->is_joystick()) joystick_count++; }
   return joystick_count;
}

AllegroFlare::PhysicalInputDevices::Joysticks::Base* InputDevicesList::find_joystick_device_by_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   // TODO: Test this function
   for (auto &device : devices)
   {
      if (device->is_joystick())
      {
         // TODO: Catch this statement below if dynamic_cast fails (which it should not, but never hurts)
         AllegroFlare::PhysicalInputDevices::Joysticks::Base *device_as_joystick =
            dynamic_cast<AllegroFlare::PhysicalInputDevices::Joysticks::Base*>(device);

         if (device_as_joystick->is_using_al_joystick(al_joystick)) return device_as_joystick;
      }
   }
   return nullptr;
}

bool InputDevicesList::joystick_device_exists_with_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   return (find_joystick_device_by_al_joystick(al_joystick) != nullptr);
}

void InputDevicesList::handle_reconfigured_joystick()
{
   // TODO: Implement this function

   // Handle *new* joysticks added
   al_reconfigure_joysticks();
   int num_joysticks = al_get_num_joysticks();
   for (int i=0; i<num_joysticks; i++)
   {
      ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(i);

      // TODO: consider the following data
      //al_get_joystick_active
      //al_get_joystick_name
      //al_get_joystick_stick_name
      //al_get_joystick_axis_name
      //al_get_joystick_button_name
      //al_get_joystick_stick_flags
      //al_get_joystick_num_sticks
      //al_get_joystick_num_axes
      //al_get_joystick_num_buttons
      //al_get_joystick_state

      bool joystick_already_exists = joystick_device_exists_with_al_joystick(al_joystick);
      if (!joystick_already_exists)
      {
         AllegroFlare::PhysicalInputDevices::Joysticks::Base *joystick =
            new AllegroFlare::PhysicalInputDevices::Joysticks::Base();
         joystick->set_al_joystick(al_joystick);
         devices.push_back(joystick);
      }
   }

   // Handle *existing* joysticks that have disconnected
   // TODO ^^
   return;
}

int InputDevicesList::num_known_devices()
{
   return devices.size();
}


} // namespace AllegroFlare


