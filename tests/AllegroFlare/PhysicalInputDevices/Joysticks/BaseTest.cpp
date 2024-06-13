
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
   EXPECT_THROW_GUARD_ERROR(
      generic_joystick.setup(),
      "AllegroFlare::PhysicalInputDevices::Joysticks::Base::setup",
      "al_joystick"
   );
}


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest,
   DISABLED__INTERACTIVE__setup__will_not_blow_up)
{
   // NOTE: These tests appear flakey!  They will work, then not work, then stall.  I think it's related to
   // some bug in Allegro5. Needs to be investigated.
   // TODO: Fix this flakey test

   al_init();
   al_install_joystick();
   if (al_get_num_joysticks() == 0)
   {
      al_uninstall_joystick();
      al_uninstall_system();
      GTEST_SKIP() << "This test requires a joystick that is acitvely plugged in.";
   }

   ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(0);
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   generic_joystick.set_al_joystick(al_joystick);
   generic_joystick.setup();

   al_uninstall_joystick();
   al_uninstall_system();
}


TEST(AllegroFlare_PhysicalInputDevices_Joysticks_BaseTest,
   DISABLED__INTERACTIVE__setup__will_fill_the_properties_with_the_expected_values)
{
   // NOTE: These tests appear flakey!  They will work, then not work, then stall.  I think it's related to
   // some bug in Allegro5. Needs to be investigated.
   // TODO: Fix this flakey test

   al_init();

   al_install_joystick();
   if (al_get_num_joysticks() == 0)
   {
      al_uninstall_joystick();
      al_uninstall_system();
      //GTEST_SKIP() << "This test requires a joystick that is acitvely plugged in.";
      GTEST_FAIL() << "This test requires a joystick that is acitvely plugged in.";
   }

   ALLEGRO_JOYSTICK *al_joystick = al_get_joystick(0);
   AllegroFlare::PhysicalInputDevices::Joysticks::Base generic_joystick;
   generic_joystick.set_al_joystick(al_joystick);

   generic_joystick.setup();

   std::string expected_joystick_name = "Joystick"; // TODO: Update Allegro5 to have better names for devices, see:
                          // https://github.com/liballeg/allegro5/blob/master/src/macosx/hidjoy.m#L733-L738

   EXPECT_EQ(expected_joystick_name, generic_joystick.get_name());

   std::map<uint32_t, std::string> expected_buttons = {
      { 0,  "Button 0"  },
      { 1,  "Button 1"  },
      { 2,  "Button 2"  },
      { 3,  "Button 3"  },
      { 4,  "Button 4"  },
      { 5,  "Button 5"  },
      { 6,  "Button 6"  },
      { 7,  "Button 7"  },
      { 8,  "Button 8"  },
      { 9,  "Button 9"  },
      { 10, "Button 10" },
      { 11, "Button 11" },
      { 12, "Button 12" },
      { 13, "Button 13" },
      { 14, "Button 14" },
   };
   EXPECT_EQ(expected_buttons, generic_joystick.get_buttons());

   al_uninstall_joystick();
   al_uninstall_system();
}


