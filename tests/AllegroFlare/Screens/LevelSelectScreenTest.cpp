
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/LevelSelectScreen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Screens_LevelSelectScreenTest : public ::testing::Test {};
class AllegroFlare_Screens_LevelSelectScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_LevelSelectScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(AllegroFlare_Screens_LevelSelectScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::LevelSelectScreen level_select_screen;
}


TEST_F(AllegroFlare_Screens_LevelSelectScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::LevelSelectScreen level_select_screen;
   EXPECT_EQ("AllegroFlare/Screens/LevelSelectScreen", level_select_screen.get_type());
}


TEST_F(AllegroFlare_Screens_LevelSelectScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::LevelSelectScreen level_select_screen;
   EXPECT_EQ(AllegroFlare::Screens::LevelSelectScreen::TYPE, level_select_screen.get_type());
}


TEST_F(AllegroFlare_Screens_LevelSelectScreenTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::LevelSelectScreen level_select_screen;
   level_select_screen.set_event_emitter(get_framework_event_emitter());
   level_select_screen.set_bitmap_bin(get_framework_bitmap_bin());
   level_select_screen.set_font_bin(get_framework_font_bin());
   level_select_screen.set_model_bin(get_framework_model_bin());
   level_select_screen.initialize();

   framework_register_and_activate_screen("level_select_screen", &level_select_screen);

   framework_run_loop(3);
}


