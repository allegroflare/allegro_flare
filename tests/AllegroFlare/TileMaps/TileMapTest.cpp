
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


