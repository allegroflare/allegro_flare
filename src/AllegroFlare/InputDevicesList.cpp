

#include <AllegroFlare/InputDevicesList.hpp>

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>
#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>
#include <algorithm>
#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>


namespace AllegroFlare
{


InputDevicesList::InputDevicesList()
   : devices({})
   , first_time_connected_joysticks_after_reconfiguration({})
   , previously_known_joysticks_connected_after_reconfiguration({})
   , previously_known_joysticks_disconnected_after_reconfiguration({})
   , updated_at(0.0f)
{
}


InputDevicesList::~InputDevicesList()
{
}


std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_first_time_connected_joysticks_after_reconfiguration() const
{
   return first_time_connected_joysticks_after_reconfiguration;
}


std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_previously_known_joysticks_connected_after_reconfiguration() const
{
   return previously_known_joysticks_connected_after_reconfiguration;
}


std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_previously_known_joysticks_disconnected_after_reconfiguration() const
{
   return previously_known_joysticks_disconnected_after_reconfiguration;
}


float InputDevicesList::get_updated_at() const
{
   return updated_at;
}


void InputDevicesList::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDevicesList::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDevicesList::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   // create a keyboard (if it is installed)
   if (al_is_keyboard_installed())
   {
      AllegroFlare::PhysicalInputDevices::Keyboard *keyboard = new AllegroFlare::PhysicalInputDevices::Keyboard();
      keyboard->set_connected(true);
      devices.push_back(keyboard);
   }

   // Create joysticks (for any that are connected)
   al_reconfigure_joysticks();
   int num_joysticks = al_get_num_joysticks();
   for (int i=0; i<num_joysticks; i++)
   {
      ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(i);
      AllegroFlare::PhysicalInputDevices::Joysticks::Base *joystick = create_new_joystick(al_joystick);
      joystick->set_connected(true);

      devices.push_back(joystick);
   }

   updated_at = al_get_time(); // TODO: pass in even time

   return;
}

int InputDevicesList::num_devices()
{
   return devices.size();
}

int InputDevicesList::num_keyboard_devices()
{
   int keyboard_count = 0;
   for (auto &device : devices) { if (device->is_keyboard()) keyboard_count++; }
   return keyboard_count;
}

int InputDevicesList::num_joystick_devices()
{
   int joystick_count = 0;
   for (auto &device : devices) { if (device->is_joystick()) joystick_count++; }
   return joystick_count;
}

int InputDevicesList::num_connected_devices()
{
   int connected_count = 0;
   for (auto &device : devices) { if (device->get_connected()) connected_count++; }
   return connected_count;
}

int InputDevicesList::num_disconnected_devices()
{
   int connected_count = 0;
   for (auto &device : devices) { if (!device->get_connected()) connected_count++; }
   return connected_count;
}

bool InputDevicesList::all_devices_are_connected()
{
   for (auto &device : devices) { if (!device->get_connected()) return false; }
   return true;
}

std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_connected_joysticks()
{
   std::vector<AllegroFlare::PhysicalInputDevices::Base*> result;
   for (auto &device : devices)
   {
      if (device->is_joystick() && device->get_connected()) result.push_back(device);
   }
   return result;
}

std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_disconnected_joysticks()
{
   std::vector<AllegroFlare::PhysicalInputDevices::Base*> result;
   for (auto &device : devices)
   {
      if (device->is_joystick() && !device->get_connected()) result.push_back(device);
   }
   return result;
}

int InputDevicesList::num_connected_joysticks()
{
   int count = 0;
   for (auto &device : devices)
   {
      if (device->is_joystick() && device->get_connected()) count++;
   }
   return count;
}

int InputDevicesList::num_joysticks_connected_after_last_reconfiguration()
{
   return previously_known_joysticks_connected_after_reconfiguration.size() +
      first_time_connected_joysticks_after_reconfiguration.size();
}

int InputDevicesList::num_joysticks_disconnected_after_last_reconfiguration()
{
   return previously_known_joysticks_disconnected_after_reconfiguration.size();
}

std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_joysticks_connected_after_last_reconfiguration()
{
   std::unordered_set<AllegroFlare::PhysicalInputDevices::Base*> unique_joysticks;

   // Insert elements from the first vector
   unique_joysticks.insert(
      first_time_connected_joysticks_after_reconfiguration.begin(),
      first_time_connected_joysticks_after_reconfiguration.end()
   );

   // Insert elements from the second vector
   unique_joysticks.insert(
      previously_known_joysticks_connected_after_reconfiguration.begin(),
      previously_known_joysticks_connected_after_reconfiguration.end()
   );

   // Convert unordered_set back to vector
   return std::vector<AllegroFlare::PhysicalInputDevices::Base*>(unique_joysticks.begin(), unique_joysticks.end());
}

std::vector<AllegroFlare::PhysicalInputDevices::Base*> InputDevicesList::get_joysticks_disconnected_after_last_reconfiguration()
{
   return previously_known_joysticks_disconnected_after_reconfiguration;
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

AllegroFlare::PhysicalInputDevices::Joysticks::Base* InputDevicesList::create_new_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   if (!(al_joystick))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDevicesList::create_new_joystick]: error: guard \"al_joystick\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDevicesList::create_new_joystick]: error: guard \"al_joystick\" not met");
   }
   AllegroFlare::PhysicalInputDevices::Joysticks::Base *joystick =
      new AllegroFlare::PhysicalInputDevices::Joysticks::Base();
   joystick->set_al_joystick(al_joystick);
   joystick->setup(); // Will populate the joystick name, button names, etc on this Joystick
   return joystick;
}

void InputDevicesList::handle_reconfigured_joystick()
{
   bool list_is_modified = false;

   std::vector<AllegroFlare::PhysicalInputDevices::Base*>
      previously_known_joysticks_connected_at_start = get_connected_joysticks();
   previously_known_joysticks_connected_after_reconfiguration.clear();
   previously_known_joysticks_disconnected_after_reconfiguration.clear();
   first_time_connected_joysticks_after_reconfiguration.clear();

   // Capture the joystick changes
   al_reconfigure_joysticks();
   double reconfiguration_occurred_at = al_get_time(); // TODO: Pass in event time

   // Handle *new* joysticks added
   int num_joysticks = al_get_num_joysticks();
   for (int i=0; i<num_joysticks; i++)
   {
      ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(i);

      AllegroFlare::PhysicalInputDevices::Joysticks::Base *joystick =
         find_joystick_device_by_al_joystick(al_joystick);
      bool joystick_is_known = (joystick != nullptr);

      if (!joystick_is_known)
      {
         // This is a newly connected joystick
         joystick = create_new_joystick(al_joystick);
         devices.push_back(joystick);

         list_is_modified = true;

         first_time_connected_joysticks_after_reconfiguration.push_back(joystick);
      }

      if (!joystick->get_connected())
      {
         joystick->set_connected(true);
         list_is_modified = true;
      }

      if (joystick_is_known)
      {
         // This is an already known joystick that is connected (includes both continues to be connected
         // or re-connected)
         previously_known_joysticks_connected_after_reconfiguration.push_back(joystick);
      }
   }

   // Pick out known joysticks that have become disconnected in this reconfiguration
   std::set_difference(
      previously_known_joysticks_connected_at_start.begin(),
      previously_known_joysticks_connected_at_start.end(),
      previously_known_joysticks_connected_after_reconfiguration.begin(),
      previously_known_joysticks_connected_after_reconfiguration.end(),
      std::back_inserter(previously_known_joysticks_disconnected_after_reconfiguration)
   );

   // Mark existing connected joysticks as disconnected
   for (auto &previously_known_joystick_that_became_disconnected
      : previously_known_joysticks_disconnected_after_reconfiguration)
   {
      previously_known_joystick_that_became_disconnected->set_connected(false);
      list_is_modified = true;
   }

   if (list_is_modified) updated_at = reconfiguration_occurred_at;

   return;
}


} // namespace AllegroFlare


