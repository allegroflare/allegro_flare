
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/AutoTile/Filters/SixteenEdges.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/TileMaps/Basic2D.hpp>

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
   result_matrix__after_process__will_have_each_value_in_the_result_matrix_filled_with_tile_expected_value__test_1)
{
   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 0, 0, 0, 0 },
         { 0, 1, 1, 1 },
         { 1, 1, 1, 1 },
         { 1, 1, 1, 1 }, // TODO: test cases for bottom left edge (and other edge case) tiles that take into
                         // account *_matrix_offset_x and *_matrix_offset_y
      })
   );

   EXPECT_EQ(true, filter.process());

   auto result_matrix = filter.get_result_matrix();

   std::vector<std::vector<int>> expected_matrix = {
      { 0,   0,  0,  0 },
      { 0,   6,  6,  6 },
      { 6,   1,  1,  1 },
      { 22, 22, 22, 22 },
   };

   EXPECT_EQ(expected_matrix, result_matrix.get_matrix());
}


TEST_F(AllegroFlare_TileMaps_AutoTile_Filters_SixteenEdgesTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__will_be_useful_for_basic_tilemaps)
{
   // Build our basic tile map

   AllegroFlare::TileMaps::Basic2D basic2d_tile_map(&get_bitmap_bin_ref());
   basic2d_tile_map.set_atlas_configuration("autotile-tileset-1-02.png", 16, 16);
   basic2d_tile_map.initialize();
   basic2d_tile_map.resize(24, 12);


   // Create our filter and build our input matrix

   AllegroFlare::TileMaps::AutoTile::Filters::SixteenEdges filter;
   filter.set_input_matrix(
      AllegroFlare::TileMaps::AutoTile::FilterMatrix::build({
         { 0, 0, 0, 0 },
         { 0, 1, 1, 1 },
         { 1, 1, 1, 1 },
         { 1, 1, 1, 1 },
      })
   );


   // Get our collision tile map from the basic tile map and fill it (skipping this step)

   //AllegroFlare::TileMaps::TileMap<int> &basic2d_tile_map_collision_tile_map =
      //basic2d_tile_map.get_collision_tile_map_ref();


   // Apply the filter to the input matrix

   EXPECT_EQ(true, filter.process());


   // Assign the values of our result matrix into the tile map

   AllegroFlare::TileMaps::AutoTile::FilterMatrix &result_matrix = filter.get_result_matrix_ref();
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = basic2d_tile_map.get_prim_mesh_ref();
   for (int y=0; y<result_matrix.get_height(); y++)
      for (int x=0; x<result_matrix.get_width(); x++)
      {
         int result_tile_value = result_matrix.get_tile(x, y);
         prim_mesh.set_tile_id(x, y, result_tile_value);
      }


   // Tweak the appearance of the tilemap for clearer presentation

   basic2d_tile_map.rescale_tile_dimensions_to(32, 32);
   AllegroFlare::Placement2D place = build_centered_placement(
      basic2d_tile_map.infer_real_width(),
      basic2d_tile_map.infer_real_height()
   );
   place.scale = {2.0, 2.0};


   // Render our result

   clear();

   place.start_transform();
   basic2d_tile_map.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


