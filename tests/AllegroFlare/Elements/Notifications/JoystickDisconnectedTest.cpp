
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Notifications/JoystickDisconnected.hpp>


TEST(AllegroFlare_Elements_Notifications_JoystickDisconnectedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Notifications::JoystickDisconnected joystick_disconnected;
}


TEST(AllegroFlare_Elements_Notifications_JoystickDisconnectedTest, has_the_expected_type)
{
   AllegroFlare::Elements::Notifications::JoystickDisconnected joystick_disconnected;
   EXPECT_EQ("JoystickDisconnected", joystick_disconnected.get_type());
}


