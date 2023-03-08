
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/PhysicalInputDeviceList.hpp>

#include <allegro5/allegro.h>


TEST(AllegroFlare_PhysicalInputDeviceListTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDeviceList physical_input_device_list;
}


TEST(AllegroFlare_PhysicalInputDeviceListTest, initialize__without_allegro_installed__will_throw_an_error)
{
   AllegroFlare::PhysicalInputDeviceList physical_input_device_list;
   std::string expected_error_message =
      "PhysicalInputDeviceList::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(physical_input_device_list.initialize(), std::runtime_error, expected_error_message);
}


TEST(AllegroFlare_PhysicalInputDeviceListTest, initialize__will_not_blow_up)
{
   al_init();
   AllegroFlare::PhysicalInputDeviceList physical_input_device_list;
   physical_input_device_list.initialize();
   al_uninstall_system();
}


TEST(AllegroFlare_PhysicalInputDeviceListTest,
   initialize__when_the_keyboard_is_not_installed__will_not_create_a_keybord_device)
{
   al_init();
   AllegroFlare::PhysicalInputDeviceList physical_input_device_list;
   physical_input_device_list.initialize();
   std::vector<AllegroFlare::PhysicalInputDevices::Base*> devices = physical_input_device_list.get_devices_ref();
   bool contains_keyboard = false;
   for (auto &device : devices)
   {
      if (device->is_keyboard())
      {
         contains_keyboard = true;
         break;
      }
   }
   EXPECT_EQ(false, contains_keyboard);
   al_uninstall_system();
}


TEST(AllegroFlare_PhysicalInputDeviceListTest, initialize__when_the_keyboard_is_installed__will_create_a_keybord_device)
{
   al_init();
   al_install_keyboard();
   AllegroFlare::PhysicalInputDeviceList physical_input_device_list;
   physical_input_device_list.initialize();
   std::vector<AllegroFlare::PhysicalInputDevices::Base*> devices = physical_input_device_list.get_devices_ref();
   bool contains_keyboard = false;
   for (auto &device : devices)
   {
      if (device->is_keyboard())
      {
         contains_keyboard = true;
         break;
      }
   }
   EXPECT_EQ(true, contains_keyboard);
   al_uninstall_keyboard();
   al_uninstall_system();
}


