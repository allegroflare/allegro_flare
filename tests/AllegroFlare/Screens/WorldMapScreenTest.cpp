
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/WorldMapScreen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

class AllegroFlare_Screens_WorldMapScreenTest : public ::testing::Test {};
class AllegroFlare_Screens_WorldMapScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_WorldMapScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};



TEST_F(AllegroFlare_Screens_WorldMapScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::WorldMapScreen world_map_screen;
}


TEST_F(AllegroFlare_Screens_WorldMapScreenTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Screens::WorldMapScreen world_map_screen;
   EXPECT_EQ("AllegroFlare/Screens/WorldMapScreen", world_map_screen.get_type());
}


TEST_F(AllegroFlare_Screens_WorldMapScreenTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::WorldMapScreen world_map_screen;
   EXPECT_EQ(AllegroFlare::Screens::WorldMapScreen::TYPE, world_map_screen.get_type());
}


TEST_F(AllegroFlare_Screens_WorldMapScreenTestWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::WorldMapScreen world_map_screen;
   world_map_screen.set_bitmap_bin(get_framework_bitmap_bin());
   world_map_screen.set_font_bin(get_framework_font_bin());
   world_map_screen.initialize();

   framework_register_and_activate_screen("world_map_screen", &world_map_screen);

   framework_run_loop(3);
}


