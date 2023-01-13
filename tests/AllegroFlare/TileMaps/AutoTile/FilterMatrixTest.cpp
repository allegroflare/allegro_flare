
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


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, resize__will_set_the_width_and_height_of_the_matrix)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   filter_matrix.resize(8, 3);
   EXPECT_EQ(8, filter_matrix.get_width());
   EXPECT_EQ(3, filter_matrix.get_height());
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, resize__will_clear_all_tiles_to_a_value_of_zero)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   filter_matrix.resize(4, 3);

   std::vector<std::vector<int>> expected_matrix = {
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
      { 0, 0, 0, 0 },
   };

   EXPECT_EQ(expected_matrix, filter_matrix.get_matrix());
}


