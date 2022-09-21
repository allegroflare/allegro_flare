
#include <gtest/gtest.h>

#include <WickedDemos/FunzDemo.hpp>

TEST(WickedDemos_FunzDemoTest, can_be_created_without_blowing_up)
{
   FunzDemo funz_demo;
}


TEST(WickedDemos_FunzDemoTest, DISABLED__INTERACTIVE__run__will_run_the_application)
{
   FunzDemo::run();
}


