
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/JoystickConfiguration.hpp>


TEST(AllegroFlare_Screens_JoystickConfigurationTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::JoystickConfiguration joystick_configuration;
}


TEST(AllegroFlare_Screens_JoystickConfigurationTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::JoystickConfiguration joystick_configuration;
   EXPECT_EQ("AllegroFlare/Screens/JoystickConfiguration", joystick_configuration.get_type());
}


TEST(AllegroFlare_Screens_JoystickConfigurationTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::JoystickConfiguration joystick_configuration;
   EXPECT_EQ(AllegroFlare::Screens::JoystickConfiguration::TYPE, joystick_configuration.get_type());
}


