
#include <gtest/gtest.h>

#include <WickedDemos/FunzDemo.hpp>

TEST(WickedDemos_FunzDemoTest, can_be_created_without_blowing_up)
{
   // DISABLED probably because the use of legacy shader requires FunzDemo to initialize during construction
   FunzDemo funz_demo;
}


TEST(WickedDemos_FunzDemoTest, run__will_run_the_application)
{
   FunzDemo::run();
}


