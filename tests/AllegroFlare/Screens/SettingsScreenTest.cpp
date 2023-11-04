
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/SettingsScreen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Screens_SettingsScreenTest : public ::testing::Test {};
class AllegroFlare_Screens_SettingsScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_SettingsScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};


void static my_on_exit_callback_func(AllegroFlare::Screens::SettingsScreen *screen, void *user_data)
{
   // Nothing to do
}


void static my_on_exit_callback_counter_func(AllegroFlare::Screens::SettingsScreen *screen, void *user_data)
{
   (*((int*)user_data))++;
}


TEST_F(AllegroFlare_Screens_SettingsScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::SettingsScreen settings_screen;
}


TEST_F(AllegroFlare_Screens_SettingsScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::SettingsScreen settings_screen;
   EXPECT_EQ("AllegroFlare/Screens/SettingsScreen", settings_screen.get_type());
}


TEST_F(AllegroFlare_Screens_SettingsScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::SettingsScreen settings_screen;
   EXPECT_EQ(AllegroFlare::Screens::SettingsScreen::TYPE, settings_screen.get_type());
}


TEST_F(AllegroFlare_Screens_SettingsScreenTest, exit_screen__when_called__will_call_on_exit_callback_func)
{
   AllegroFlare::Screens::SettingsScreen settings_screen;
   int callback_calls = 0;
   settings_screen.set_on_exit_callback_func(my_on_exit_callback_counter_func);
   settings_screen.set_on_exit_callback_func_user_data(&callback_calls);

   settings_screen.exit_screen();
   EXPECT_EQ(1, callback_calls);

   settings_screen.exit_screen();
   EXPECT_EQ(2, callback_calls);

   settings_screen.exit_screen();
   EXPECT_EQ(3, callback_calls);
}


TEST_F(AllegroFlare_Screens_SettingsScreenTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::SettingsScreen settings_screen;
   settings_screen.set_event_emitter(get_framework_event_emitter());
   settings_screen.set_bitmap_bin(get_framework_bitmap_bin());
   settings_screen.set_font_bin(get_framework_font_bin());
   settings_screen.set_model_bin(get_framework_model_bin());
   settings_screen.set_on_exit_callback_func(my_on_exit_callback_func);
   settings_screen.initialize();

   framework_register_and_activate_screen("settings_screen", &settings_screen);

   framework_run_loop(3);
}


