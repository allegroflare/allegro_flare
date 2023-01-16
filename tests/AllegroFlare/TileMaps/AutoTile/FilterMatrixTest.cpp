
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/FilterMatrix.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>


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


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, set_tile__will_set_the_tile_at_the_coordinate)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   filter_matrix.resize(4, 3);

   filter_matrix.set_tile(1, 2, 7);
   filter_matrix.set_tile(3, 1, 9);
   filter_matrix.set_tile(0, 0, 6);

   std::vector<std::vector<int>> expected_matrix = {
      { 6, 0, 0, 0 },
      { 0, 0, 0, 9 },
      { 0, 7, 0, 0 },
   };

   EXPECT_EQ(expected_matrix, filter_matrix.get_matrix());
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest,
   set_tile__setting_coordinates_outsize_the_dimensions__will_throw_an_error)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix;
   filter_matrix.resize(4, 3);

   EXPECT_THROW_GUARD_ERROR(filter_matrix.set_tile(-1, 0, 999), "FilterMatrix::set_tile", "(x >= 0)");
   EXPECT_THROW_GUARD_ERROR(filter_matrix.set_tile(4, 0, 999), "FilterMatrix::set_tile", "(x < get_width())");
   EXPECT_THROW_GUARD_ERROR(filter_matrix.set_tile(0, -1, 999), "FilterMatrix::set_tile", "(y >= 0)");
   EXPECT_THROW_GUARD_ERROR(filter_matrix.set_tile(0, 3, 999), "FilterMatrix::set_tile", "(y < get_height())");
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest, build__will_build_a_matrix_with_the_expected_data)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix = 
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 6, 0, 0, 0 },
         { 0, 0, 0, 9 },
         { 0, 7, 0, 0 },
      });

   std::vector<std::vector<int>> expected_matrix = {
      { 6, 0, 0, 0 },
      { 0, 0, 0, 9 },
      { 0, 7, 0, 0 },
   };

   EXPECT_EQ(expected_matrix, filter_matrix.get_matrix());
}


TEST(AllegroFlare_TileMaps_AutoTile_FilterMatrixTest,
   tile_matches_with_extruded_boundaries__when_out_of_bounds__will_return_true_if_the_closest_tile_matches)
{
   AllegroFlare::TileMaps::AutoTile::FilterMatrix filter_matrix = 
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 1,  2,  3,  4 },
         { 12, 0,  0,  5 },
         { 11, 0,  0,  6 },
         { 10, 9,  8,  7 },
      });

   EXPECT_EQ(true, filter_matrix.tile_matches_with_extruded_boundaries(-1, -1, 1));
}


