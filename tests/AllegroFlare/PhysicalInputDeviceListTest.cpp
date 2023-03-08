
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


