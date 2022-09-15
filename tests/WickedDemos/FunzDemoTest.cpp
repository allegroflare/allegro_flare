
#include <gtest/gtest.h>

#include <WickedDemos/FunzDemo.hpp>

TEST(WickedDemos_FunzDemoTest, DISABLED__can_be_created_without_blowing_up)
{
   // DISABLED probably because the use of legacy shader requires FunzDemo to initialize during construction
   FunzDemo funz_demo;
}

