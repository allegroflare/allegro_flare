
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/DisplaySettings.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
#include <AllegroFlare/DisplaySettingsInterfaces/Base.hpp>
#include <AllegroFlare/DisplaySettingsInterfaces/Live.hpp>
#include <AllegroFlare/Testing/AllegroFlare/DisplaySettingsInterfaces/DisplayMock.hpp>


class MyTestDisplaySettingsInterface : public AllegroFlare::DisplaySettingsInterfaces::Base
{
public:
   MyTestDisplaySettingsInterface()
      : AllegroFlare::DisplaySettingsInterfaces::Base("TestDisplaySettingsInterface")
   {}
};


class AllegroFlare_Screens_DisplaySettingsTest : public ::testing::Test {};
class AllegroFlare_Screens_DisplaySettingsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_DisplaySettingsTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


void static my_on_exit_callback_func(AllegroFlare::Screens::DisplaySettings *screen, void *user_data)
{
   // Nothing to do
}


void static my_on_exit_callback_counter_func(AllegroFlare::Screens::DisplaySettings *screen, void *user_data)
{
   (*((int*)user_data))++;
}


TEST_F(AllegroFlare_Screens_DisplaySettingsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::DisplaySettings display_settings_screen;
}


TEST_F(AllegroFlare_Screens_DisplaySettingsTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::DisplaySettings display_settings_screen;
   EXPECT_EQ("AllegroFlare/Screens/DisplaySettings", display_settings_screen.get_type());
}


TEST_F(AllegroFlare_Screens_DisplaySettingsTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::DisplaySettings display_settings_screen;
   EXPECT_EQ(AllegroFlare::Screens::DisplaySettings::TYPE, display_settings_screen.get_type());
}


TEST_F(AllegroFlare_Screens_DisplaySettingsTest, exit_screen__when_called__will_call_on_exit_callback_func)
{
   AllegroFlare::Screens::DisplaySettings display_settings_screen;
   int callback_calls = 0;
   display_settings_screen.set_on_exit_callback_func(my_on_exit_callback_counter_func);
   display_settings_screen.set_on_exit_callback_func_user_data(&callback_calls);

   display_settings_screen.exit_screen();
   EXPECT_EQ(1, callback_calls);

   display_settings_screen.exit_screen();
   EXPECT_EQ(2, callback_calls);

   display_settings_screen.exit_screen();
   EXPECT_EQ(3, callback_calls);
}


// TODO: Add test that does not use AllegroFlare::Frameworks::Full


TEST_F(AllegroFlare_Screens_DisplaySettingsTestWithAllegroFrameworksFullFixture,
   CAPTURE__TIMED_INTERACTIVE__will_run_as_expected)
{
   // Custom local class option:
   //MyTestDisplaySettingsInterface display_settings_interface;
   // This is a "live" option:
   //AllegroFlare::DisplaySettingsInterfaces::Live display_settings_interface;
   //display_settings_interface.set_display(get_framework_ref().get_primary_display()->al_display);
   // Pure mock option:
   AllegroFlare::Testing::AllegroFlare::DisplaySettingsInterfaces::DisplayMock display_settings_interface;

   bool inhibited = al_inhibit_screensaver(true);
   if (inhibited) display_settings_interface.manually_mark_screensaver_as_inhibited();

   AllegroFlare::Screens::DisplaySettings display_settings_screen;
   display_settings_screen.set_event_emitter(get_framework_event_emitter());
   display_settings_screen.set_bitmap_bin(get_framework_bitmap_bin());
   display_settings_screen.set_font_bin(get_framework_font_bin());
   display_settings_screen.set_model_bin(get_framework_model_bin());
   display_settings_screen.set_display_settings_interface(&display_settings_interface);
   display_settings_screen.set_on_exit_callback_func(my_on_exit_callback_func);
   display_settings_screen.initialize();

   framework_register_and_activate_screen("display_settings_screen", &display_settings_screen);

   framework_run_loop(3);
}


