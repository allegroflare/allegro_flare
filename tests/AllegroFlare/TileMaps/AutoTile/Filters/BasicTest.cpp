
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


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicTest,
   result_matrix__after_process__will_have_the_same_width_and_height_as_the_input_matrix)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Basic basic_filter;
   AllegroFlare::TileMaps::AutoTile::FilterMatrix matrix;
   matrix.resize(7, 9);
   basic_filter.set_input_matrix(matrix);

   EXPECT_EQ(true, basic_filter.process());

   auto result_matrix = basic_filter.get_result_matrix();

   EXPECT_EQ(matrix.get_width(), result_matrix.get_width());
   EXPECT_EQ(matrix.get_height(), result_matrix.get_height());
}


TEST(AllegroFlare_TileMaps_AutoTile_Filters_BasicTest,
   result_matrix__after_process__will_have_each_value_in_the_result_matrix_filled_with_tile_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::Basic basic_filter(7);
   basic_filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 0, 0, 0, 0 },
         { 0, 0, 0, 0 },
         { 0, 0, 0, 0 },
      })
   );

   EXPECT_EQ(true, basic_filter.process());

   auto result_matrix = basic_filter.get_result_matrix();

   std::vector<std::vector<int>> expected_matrix = {
      { 7, 7, 7, 7 },
      { 7, 7, 7, 7 },
      { 7, 7, 7, 7 },
   };

   EXPECT_EQ(expected_matrix, result_matrix.get_matrix());
}


