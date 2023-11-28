
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Locations/Player.hpp>


TEST(AllegroFlare_WorldMaps_Locations_PlayerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Locations::Player player;
}


TEST(AllegroFlare_WorldMaps_Locations_PlayerTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Locations/Player",
     AllegroFlare::WorldMaps::Locations::Player::TYPE
   );
}


TEST(AllegroFlare_WorldMaps_Locations_PlayerTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Locations::Player player;
   EXPECT_EQ(AllegroFlare::WorldMaps::Locations::Player::TYPE, player.get_type());
}


