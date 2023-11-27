
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>


TEST(AllegroFlare_WorldMaps_Maps_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Maps::Basic basic;
}


TEST(AllegroFlare_WorldMaps_Maps_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Maps/Basic",
     AllegroFlare::WorldMaps::Maps::Basic::TYPE
   );
}


TEST(AllegroFlare_WorldMaps_Maps_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Maps::Basic basic;
   EXPECT_EQ(AllegroFlare::WorldMaps::Maps::Basic::TYPE, basic.get_type());
}


