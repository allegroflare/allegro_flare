
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Keyframe.hpp>


TEST(AllegroFlare_Timeline_KeyframeTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::Keyframe keyframe;
}


TEST(AllegroFlare_Timeline_KeyframeTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::Keyframe keyframe;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, keyframe.run());
}

