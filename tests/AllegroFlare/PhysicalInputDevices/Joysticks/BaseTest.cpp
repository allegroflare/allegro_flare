
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
}


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   EXPECT_EQ("AllegroFlare/PhysicalInputDevices/Joysticks/Base", generic_joystick.get_type());
}


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevices::Joysticks::Base::TYPE, generic_joystick.get_type());
}


