
#include <gtest/gtest.h>

#include <WickedDemos/TileDemo.hpp>


TEST(WickedDemos_TileDemoTest, can_be_created_without_blowing_up)
{
   WickedDemos::TileDemo tile_demo;
}


TEST(WickedDemos_TileDemoTest,
   //INTERACTIVE__run__runs_the_program)
   DISABLED__INTERACTIVE__run__runs_the_program)
{
   WickedDemos::TileDemo::run();
}


