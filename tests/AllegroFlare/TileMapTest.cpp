
#include <gtest/gtest.h>

#include <AllegroFlare/TileMap.hpp>


TEST(AllegroFlare_TileMapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMap<int> tile_map;
}


TEST(AllegroFlare_TileMapTest, width__has_the_expected_default_value)
{
   AllegroFlare::TileMap tile_map;
   ASSERT_EQ(0, tile_map.get_width());
}


TEST(AllegroFlare_TileMapTest, height__has_the_expected_default_value)
{
   AllegroFlare::TileMap tile_map;
   ASSERT_EQ(0, tile_map.get_height());
}


TEST(AllegroFlare_TileMapTest, get_tile__without_initialization__throws_an_error)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, set_tile__without_initialization__throws_an_error)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, get_coordinates_from_contiguous_number__when_the__returns_a_special_invalid_result)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, infer_num_tiles__will_return_the_total_number_of_tiles_in_the_tilemap)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, resize__will_set_the_width_and_height)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, resize__will_clear_all_the_tiles_to_0)
{
   // TODO
}


TEST(AllegroFlare_TileMapTest, is_dimensionless__if_the_width_or_height_is_less_than_or_equal_zero__returns_true)
{
   AllegroFlare::TileMap tile_map;
   ASSERT_EQ(true, tile_map.is_dimensionless());
}


TEST(AllegroFlare_TileMapTest, is_dimensionless__if_the_width_or_height_are_positive_numbers__returns_false)
{
   AllegroFlare::TileMap tile_map(4, 3);
   ASSERT_EQ(false, tile_map.is_dimensionless());
}


