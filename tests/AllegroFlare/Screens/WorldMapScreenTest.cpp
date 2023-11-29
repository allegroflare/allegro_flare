
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/WorldMapScreen.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>
//#include <AllegroFlare/Frameworks/Full.hpp>

#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>
#include <AllegroFlare/WorldMaps/Locations/Player.hpp>

class AllegroFlare_Screens_WorldMapScreenTest : public ::testing::Test {};
class AllegroFlare_Screens_WorldMapScreenTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Screens_WorldMapScreenTestWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{};
class AllegroFlare_Screens_WorldMapScreenTestWithMapAndWithAllegroFrameworksFullFixture
   : public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{
public:
   AllegroFlare::WorldMaps::Maps::Basic map;
   virtual void SetUp()
   {
      AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp();
      map.set_background_image_identifier("overworld-map-02.png");
      map.set_locations({
         // TODO: Come up with some better location names
         {
            "magnus_castle",
            new AllegroFlare::WorldMaps::Locations::Basic("Magnus Castle", 221, 423)
         },
         {
            "office2",
            new AllegroFlare::WorldMaps::Locations::Basic("Office2", 611, 268)
         },
         {
            "office3",
            new AllegroFlare::WorldMaps::Locations::Basic("Office3", 528, 414)
         },
         {
            "central_village",
            new AllegroFlare::WorldMaps::Locations::Basic("Central Village", 807, 428)
         },
         {
            "thorian_grove",
            new AllegroFlare::WorldMaps::Locations::Basic("Thorian Grove", 584, 713)
         },
         {
            "office6",
            new AllegroFlare::WorldMaps::Locations::Basic("Office6", 1054, 335)
         },
         {
            "merryvale_village",
            new AllegroFlare::WorldMaps::Locations::Basic("Merryvale Village", 1132, 772)
         },
         {
            "north_celestial_crossing",
            new AllegroFlare::WorldMaps::Locations::Basic("North Celestial Crossing", 1315, 473)
         },
         {
            "south_celestial_crossing",
            new AllegroFlare::WorldMaps::Locations::Basic("South Celestial Crossing", 1351, 551)
         },
         {
            "luminara",
            new AllegroFlare::WorldMaps::Locations::Basic("Luminara", 1662, 250)
         },
         {
            "crestwood_forest",
            new AllegroFlare::WorldMaps::Locations::Basic("Crestwood Forest", 961, 678)
         },
         {
            "player",
            new AllegroFlare::WorldMaps::Locations::Player(1262, 350)
         },
      });
      map.set_primary_point_of_interest_identifier("player");
   }
   virtual void TearDown()
   {
      // Cleanup
      for (auto &location : map.get_locations())
      {
         delete location.second;
         location.second = nullptr;
      }
      AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::TearDown();
   }
};




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

   framework_run_loop(1);
}


TEST_F(AllegroFlare_Screens_WorldMapScreenTestWithMapAndWithAllegroFrameworksFullFixture,
   TIMED_INTERACTIVE__will_run_as_expected)
{
   AllegroFlare::Screens::WorldMapScreen world_map_screen;
   world_map_screen.set_bitmap_bin(get_framework_bitmap_bin());
   world_map_screen.set_font_bin(get_framework_font_bin());
   world_map_screen.set_map(&map);
   world_map_screen.initialize();

   framework_register_and_activate_screen("world_map_screen", &world_map_screen);

   framework_run_loop(-1);
}


