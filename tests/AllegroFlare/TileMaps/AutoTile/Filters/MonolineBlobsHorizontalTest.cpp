
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal.hpp>


TEST(AllegroFlare_TileMaps_AutoTile_Filters_MonolineBlobsHorizontalTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal monoline_blobs_horizontal;
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_MonolineBlobsHorizontalTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/TileMaps/AutoTile/Filters/MonolineBlobsHorizontal",
     AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::TYPE
   );
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_MonolineBlobsHorizontalTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal monoline_blobs_horizontal;
   EXPECT_EQ(AllegroFlare::TileMaps::AutoTile::Filters::MonolineBlobsHorizontal::TYPE, monoline_blobs_horizontal.get_type());
}


