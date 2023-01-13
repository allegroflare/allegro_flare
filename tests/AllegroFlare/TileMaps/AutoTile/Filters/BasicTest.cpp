
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/Basic.hpp>


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Basic basic;
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicTest, TYPE__has_the_expected_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Basic basic;
   EXPECT_EQ("Filters/Basic", basic.get_type());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Basic basic;
   EXPECT_EQ(AllegroFlare::TileMaps::AutoTile::Filters::Basic::TYPE, basic.get_type());
}


