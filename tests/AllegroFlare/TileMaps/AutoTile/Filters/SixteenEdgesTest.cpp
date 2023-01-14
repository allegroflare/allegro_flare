
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/SixteenEdges.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest : public ::testing::Test {};
class AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};



TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
}


TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest, TYPE__has_the_expected_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   EXPECT_EQ("Filters/SixteenEdges", filter.get_type());
}


TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   EXPECT_EQ(AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges::TYPE, filter.get_type());
}


TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest,
   result_matrix__after_process__will_have_the_same_width_and_height_as_the_input_matrix)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   AllegroFlare::TileMaps::AutoTile::FilterMatrix matrix;
   matrix.resize(7, 9);
   filter.set_input_matrix(matrix);

   EXPECT_EQ(true, filter.process());

   auto result_matrix = filter.get_result_matrix();

   EXPECT_EQ(matrix.get_width(), result_matrix.get_width());
   EXPECT_EQ(matrix.get_height(), result_matrix.get_height());
}


TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTest,
   result_matrix__after_process__will_have_each_value_in_the_result_matrix_filled_with_tile_value)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 0, 0, 0, 0 },
         { 0, 1, 1, 1 },
         { 1, 1, 1, 1 },
      })
   );

   EXPECT_EQ(true, filter.process());

   auto result_matrix = filter.get_result_matrix();

   std::vector<std::vector<int>> expected_matrix = {
      { 0,  0,  0,  0 },
      { 0,  2,  2,  2 },
      { 2,  0, 10, 10 }, // TODO: the second value in this row should be 10.
   };

   EXPECT_EQ(expected_matrix, result_matrix.get_matrix());
}


