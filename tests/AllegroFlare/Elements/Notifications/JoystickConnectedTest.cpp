
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Notifications/JoystickConnected.hpp>


TEST(AllegroFlare_Elements_Notifications_JoystickConnectedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Notifications::JoystickConnected joystick_connected;
}


TEST(AllegroFlare_Elements_Notifications_JoystickConnectedTest, has_the_expected_type)
{
   AllegroFlare::Elements::Notifications::JoystickConnected joystick_connected;
   EXPECT_EQ("JoystickConnected", joystick_connected.get_type());
}


