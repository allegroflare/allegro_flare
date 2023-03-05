
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevice/Keyboard.hpp>


TEST(AllegroFlare_PhysicalInputDevice_KeyboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevice::Keyboard keyboard;
}


TEST(AllegroFlare_PhysicalInputDevice_KeyboardTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevice::Keyboard keyboard;
   EXPECT_EQ("AllegroFlare/PhysicalInputDevice/Keyboard", keyboard.get_type());
}


TEST(AllegroFlare_PhysicalInputDevice_KeyboardTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevice::Keyboard keyboard;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevice::Keyboard::TYPE, keyboard.get_type());
}


