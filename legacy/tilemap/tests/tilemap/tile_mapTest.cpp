

#include <gtest/gtest.h>

#include <tilemap/tile_map.hpp>


TEST(TileMapTest, set_width_and_height__sets_the_width_and_height)
{
   TileMap tile_map(10, 20, 16);

   ASSERT_EQ(10, tile_map.get_width());
   ASSERT_EQ(20, tile_map.get_height());

   tile_map.set_width_and_height(42, 15);

   ASSERT_EQ(42, tile_map.get_width());
   ASSERT_EQ(15, tile_map.get_height());
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


