
#include <gtest/gtest.h>

#include <AllegroFlare/Math.hpp>


TEST(AllegroFlare_MathTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Math math;
}


TEST(AllegroFlare_MathTest, run__returns_the_expected_response)
{
   AllegroFlare::Math math;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, math.run());
}

