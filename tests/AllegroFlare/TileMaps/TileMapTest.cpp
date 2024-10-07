
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_TileMaps_TileMapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
}


TEST(AllegroFlare_TileMaps_TileMapTest, width__has_the_expected_default_value)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   ASSERT_EQ(0, tile_map.get_num_rows());
}


TEST(AllegroFlare_TileMaps_TileMapTest, num_columns__has_the_expected_default_value)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   ASSERT_EQ(0, tile_map.get_num_columns());
}


TEST(AllegroFlare_TileMaps_TileMapTest, in_bounds__returns_true_if_the_coordinate_is_in_bounds)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, in_bounds__returns_false_if_the_coordinate_is_out_of_bounds)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, get_tile__without_initialization__throws_an_error)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, set_tile__without_initialization__throws_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   std::string expected_error_message = "[AllegroFlare::TileMaps::TileMap<T>::set_tile]: error: tile map must be "
      "initialized first.";
   EXPECT_THROW_WITH_MESSAGE(
      tile_map.set_tile(3, 2, 1),
      std::runtime_error,
      expected_error_message
   );
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   is_dimensionless__if_the_width_or_num_columns_is_less_than_or_equal_zero__returns_true)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   ASSERT_EQ(true, tile_map.is_dimensionless());
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   is_dimensionless__if_the_width_or_num_columns_are_positive_numbers__returns_false)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map(4, 3);
   ASSERT_EQ(false, tile_map.is_dimensionless());
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   get_coordinates_from_contiguous_number__when_the_map_is_dimensionless__returns_a_special_invalid_result)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, infer_num_tiles__will_return_the_total_number_of_tiles_in_the_tilemap)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, resize__will_set_the_width_and_num_columns)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, resize__will_clear_all_the_tiles_to_0)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_TileMapTest, resize__with_a_fill_value__will_clear_all_the_tiles_to_the_fill_value)
{
   // TODO
   AllegroFlare::TileMaps::TileMap<float> tile_map;
   tile_map.resize_with_fill(4, 3, 16.0f);
   EXPECT_EQ(4, tile_map.get_num_columns());
   EXPECT_EQ(3, tile_map.get_num_rows());
   for (auto &tile : tile_map.get_tiles())
   {
      EXPECT_EQ(16.0f, tile);
   }
}


TEST(AllegroFlare_TileMaps_TileMapTest, fill_with_data__will_fill_the_tiles_with_the_contents_of_the_vector)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();
   tile_map.resize_with_fill(5, 3, 0);
   tile_map.fill_with_data(std::vector<std::vector<int>>{
      { 1,   2,  3,  4,  5 },
      { 6,   7,  8,  9, 10 },
      { 11, 12, 13, 14, 15 },
   });

   EXPECT_EQ(1,  tile_map.get_tile(0, 0));
   EXPECT_EQ(7,  tile_map.get_tile(1, 1));
   EXPECT_EQ(9,  tile_map.get_tile(3, 1));
   EXPECT_EQ(11, tile_map.get_tile(0, 2));
   EXPECT_EQ(15, tile_map.get_tile(4, 2));
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   fill_with_data__when_the_number_of_rows_does_not_match_the_current_size_of_the_tile_map__will_throw_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();
   tile_map.resize_with_fill(5, 3, 0);
   EXPECT_THROW_WITH_MESSAGE(
      tile_map.fill_with_data(std::vector<std::vector<int>>{
         { 1,   2,  3,  4,  5 },
         //{ 6,   7,  8,  9, 10 },
         //{ 11, 12, 13, 14, 15 },
      }),
      std::runtime_error,
      "[AllegroFlare::TileMaps::TileMap<T>::fill_with_data]: error: The number of rows in the provided data (1) "
         "does not match the number of rows of the tile_map (3)"
   );
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   fill_with_data__when_a_row__does_not_have_the_correct_number_of_columns__will_throw_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();
   tile_map.resize_with_fill(5, 3, 0);
   EXPECT_THROW_WITH_MESSAGE(
      tile_map.fill_with_data(std::vector<std::vector<int>>{
         { 1,   2,  3,  4,  5 },
         { 6,   7,  8,  9, 10, 997, 998, 999 },
         { 11, 12, 13, 14, 15 },
      }),
      std::runtime_error,
      "[AllegroFlare::TileMaps::TileMap<T>::fill_with_data]: error: The number of columns in the provided data (8) "
         "does not match the number of columns of the tile_map (5)"
   );
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   build_data_as_2d_vector__will_return_a_copy_of_the_contents_of_the_tilemap_in_a_vector_of_vectors)
{
   // TODO: Find a way to make this test more focused and distinct from the "fill_area" test
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();
   tile_map.resize_with_fill(7, 5, 0);
   tile_map.fill_area(1, 1, 4, 2, 8);
   tile_map.set_tile(2, 3, 7);

   std::vector<std::vector<int>> actual_data = tile_map.build_data_as_2d_vector();
   std::vector<std::vector<int>> expected_data = {
      { 0, 0, 0, 0, 0, 0, 0 },
      { 0, 8, 8, 8, 8, 0, 0 },
      { 0, 8, 8, 8, 8, 0, 0 },
      { 0, 0, 7, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0 },
   };

   EXPECT_EQ(expected_data, actual_data);
}


TEST(AllegroFlare_TileMaps_TileMapTest, fill_area__will_fill_the_area_with_the_value)
{
   // TODO: Find a way to make this test more focused and distinct from the "build_data_as_2d_vector" test
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();
   tile_map.resize_with_fill(7, 5, 0);
   tile_map.fill_area(1, 1, 4, 2, 8);

   std::vector<std::vector<int>> actual_data = tile_map.build_data_as_2d_vector();
   std::vector<std::vector<int>> expected_data = {
      { 0, 0, 0, 0, 0, 0, 0 },
      { 0, 8, 8, 8, 8, 0, 0 },
      { 0, 8, 8, 8, 8, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0 },
      { 0, 0, 0, 0, 0, 0, 0 },
   };

   EXPECT_EQ(expected_data, actual_data);
}


TEST(AllegroFlare_TileMaps_TileMapTest,
   resize_and_fill_with_contiguous_data__when_given_a_size_that_does_not_match_the_params__will_throw_an_error)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();

   std::vector<int> data = {
      1,  2,  3,  4,
      5,  6,  7,  8,
      9, 10, 11, 12,
   };

   EXPECT_THROW_WITH_MESSAGE(
      tile_map.resize_and_fill_with_contiguous_data(1, 3, data),
      std::runtime_error,
      "[AllegroFlare::TileMaps::TileMap<T>::resize_and_fill_with_contiguous_data]: error: Expecting \"data.size()\" "
         "(has a value of 12) to be of equal size as \"num_rows * num_columns\" (has a value of 3)"
   );
}


// TODO: Add tests for "if (num_columns <= 0)" and "if (num_columns <= 0)" guards on
// resize_and_fill_with_contiguous_data


TEST(AllegroFlare_TileMaps_TileMapTest,
   resize_and_fill_with_contiguous_data__will_set__num_rows__num_columns__and_fill_the_data_as_expected)
{
   AllegroFlare::TileMaps::TileMap<int> tile_map;
   tile_map.initialize();

   std::vector<int> data = {
      1,  2,  3,  4,
      5,  6,  7,  8,
      9, 10, 11, 12,
   };

   tile_map.resize_and_fill_with_contiguous_data(4, 3, data);

   EXPECT_EQ(4, tile_map.get_num_columns());
   EXPECT_EQ(3, tile_map.get_num_rows());
   EXPECT_EQ(data, tile_map.get_tiles());
}


