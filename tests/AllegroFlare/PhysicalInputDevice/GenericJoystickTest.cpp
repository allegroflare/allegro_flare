
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevice/GenericJoystick.hpp>


TEST(AllegroFlare_PhysicalInputDevice_GenericJoystickTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevice::GenericJoystick generic_joystick;
}


TEST(AllegroFlare_PhysicalInputDevice_GenericJoystickTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevice::GenericJoystick generic_joystick;
   EXPECT_EQ("AllegroFlare/PhysicalInputDevice/GenericJoystick", generic_joystick.get_type());
}


TEST(AllegroFlare_PhysicalInputDevice_GenericJoystickTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevice::GenericJoystick generic_joystick;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevice::GenericJoystick::TYPE, generic_joystick.get_type());
}


