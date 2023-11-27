
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Locations/Basic.hpp>


TEST(AllegroFlare_WorldMaps_Locations_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Locations::Basic basic;
}


TEST(AllegroFlare_WorldMaps_Locations_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Locations/Basic",
     AllegroFlare::WorldMaps::Locations::Basic::TYPE
   );
}


TEST(AllegroFlare_WorldMaps_Locations_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Locations::Basic basic;
   EXPECT_EQ(AllegroFlare::WorldMaps::Locations::Basic::TYPE, basic.get_type());
}


