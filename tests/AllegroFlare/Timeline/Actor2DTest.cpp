
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Actor2D.hpp>


TEST(AllegroFlare_Timeline_Actor2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::Actor2D actor2d;
}


TEST(AllegroFlare_Timeline_Actor2DTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::Actor2D actor2d;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, actor2d.run());
}

