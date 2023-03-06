
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevices/GenericJoystick.hpp>


TEST(AllegroFlare_PhysicalInputDevices_GenericJoystickTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevices::GenericJoystick generic_joystick;
}


TEST(AllegroFlare_PhysicalInputDevices_GenericJoystickTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevices::GenericJoystick generic_joystick;
   EXPECT_EQ("AllegroFlare/PhysicalInputDevices/GenericJoystick", generic_joystick.get_type());
}


TEST(AllegroFlare_PhysicalInputDevices_GenericJoystickTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevices::GenericJoystick generic_joystick;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevices::GenericJoystick::TYPE, generic_joystick.get_type());
}


