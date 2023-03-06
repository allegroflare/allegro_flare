
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>


TEST(AllegroFlare_PhysicalInputDevices_KeyboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevices::Keyboard keyboard;
}


TEST(AllegroFlare_PhysicalInputDevices_KeyboardTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevices::Keyboard keyboard;
   EXPECT_EQ("AllegroFlare/PhysicalInputDevices/Keyboard", keyboard.get_type());
}


TEST(AllegroFlare_PhysicalInputDevices_KeyboardTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevices::Keyboard keyboard;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevices::Keyboard::TYPE, keyboard.get_type());
}


