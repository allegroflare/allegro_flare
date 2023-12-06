
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
   AllegroFlare::WorldMaps::Locations::Basic* create_basic_location(std::string name, float x, float y)
   {
      AllegroFlare::WorldMaps::Locations::Basic *result = new AllegroFlare::WorldMaps::Locations::Basic(name);
      result->set_x(x);
      result->set_y(y);
      return result;
   }
   AllegroFlare::WorldMaps::Locations::Player* create_player_location(float x, float y)
   {
      AllegroFlare::WorldMaps::Locations::Player *result = new AllegroFlare::WorldMaps::Locations::Player();
      result->set_x(x);
      result->set_y(y);
      return result;
   }
   virtual void SetUp()
   {
      AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp();
      map.set_background_image_identifier("overworld-map-02.png");
      map.set_locations({
         { "great_magnus_castle", create_basic_location("Great Magnus Castle", 221, 423) },
         { "village_of_garrick", create_basic_location("Village of Garrick", 611, 268) },
         { "dragons_ruins", create_basic_location("Dragon's Ruins", 528, 414) },
         { "central_village", create_basic_location("Central Village", 807, 428) },
         { "thorian_grove", create_basic_location("Thorian Grove", 584, 713) },
         { "whispering_mountains", create_basic_location("Whispering Mountains", 1054, 335) },
         { "merryvale_village", create_basic_location("Merryvale Village", 1132, 772) },
         { "north_celestial_crossing", create_basic_location("North Celestial Crossing", 1315, 473) },
         { "south_celestial_crossing", create_basic_location("South Celestial Crossing", 1351, 551) },
         { "luminara_citadel", create_basic_location("Luminara Citadel", 1662, 250) },
         { "crestwood_forest", create_basic_location("Crestwood Forest", 961, 678) },
         { "player", create_player_location(1262, 350) },
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

   framework_run_loop(5);
}


