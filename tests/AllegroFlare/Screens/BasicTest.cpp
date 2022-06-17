
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Basic.hpp>


TEST(AllegroFlare_Screens_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Basic basic;
}


TEST(AllegroFlare_Screens_BasicTest, run__returns_the_expected_response)
{
   AllegroFlare::Screens::Basic basic;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, basic.run());
}

