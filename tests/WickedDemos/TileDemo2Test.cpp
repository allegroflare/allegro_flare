
#include <gtest/gtest.h>

#include <WickedDemos/TileDemo2.hpp>


TEST(WickedDemos_TileDemo2Test, can_be_created_without_blowing_up)
{
   WickedDemos::TileDemo2 tile_demo;
}


TEST(WickedDemos_TileDemo2Test, run__runs_the_program)
{
   WickedDemos::TileDemo2::run();
   SUCCEED();
}


