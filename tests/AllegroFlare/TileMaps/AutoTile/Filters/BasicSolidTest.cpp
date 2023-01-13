
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/BasicSolid.hpp>


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicSolidTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid basic;
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicSolidTest, TYPE__has_the_expected_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid basic;
   EXPECT_EQ("Filters/BasicSolid", basic.get_type());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicSolidTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid basic;
   EXPECT_EQ(AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid::TYPE, basic.get_type());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicSolidTest,
   result_matrix__after_process__will_have_the_same_width_and_height_as_the_input_matrix)
{
   AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid basic_filter;
   AllegroFlare::TileMaps::AutoTile::FilterMatrix matrix;
   matrix.resize(7, 9);
   basic_filter.set_input_matrix(matrix);

   EXPECT_EQ(true, basic_filter.process());

   auto result_matrix = basic_filter.get_result_matrix();

   EXPECT_EQ(matrix.get_width(), result_matrix.get_width());
   EXPECT_EQ(matrix.get_height(), result_matrix.get_height());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicSolidTest,
   result_matrix__after_process__will_have_each_value_in_the_result_matrix_filled_with_tile_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::BasicSolid basic_filter(7);
   basic_filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 0, 0, 0, 0 },
         { 0, 1, 1, 1 },
         { 1, 1, 1, 1 },
      })
   );

   EXPECT_EQ(true, basic_filter.process());

   auto result_matrix = basic_filter.get_result_matrix();

   std::vector<std::vector<int>> expected_matrix = {
      { 0, 0, 0, 0 },
      { 0, 7, 7, 7 },
      { 7, 7, 7, 7 },
   };

   EXPECT_EQ(expected_matrix, result_matrix.get_matrix());
}

