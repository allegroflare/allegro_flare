
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, width__will_be_set_to_0_by_default)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   EXPECT_EQ(0, filter_matrix.get_width());
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, height__will_be_set_to_0_by_default)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   EXPECT_EQ(0, filter_matrix.get_height());
}


