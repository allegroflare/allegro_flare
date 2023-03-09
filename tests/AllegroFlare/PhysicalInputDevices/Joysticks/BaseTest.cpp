
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


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


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest, setup__without_an_al_joystick__will_throw_an_error)
{
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   EXPECT_THROW_GUARD_ERROR(generic_joystick.setup(), "Base::setup", "al_joystick");
}


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest,
   INTERACTIVE__setup__will_fill_the_properties_with_the_expected_values)
{
   al_init();
   al_install_joystick();
   if (al_get_num_joysticks() == 0)
   {
      GTEST_SKIP() << "This test requires a joystick that is acitvely plugged in.";
   }

   ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(0);
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   generic_joystick.set_al_joystick(al_joystick);

   al_uninstall_joystick();
   al_uninstall_system();
}


