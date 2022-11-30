
#include <gtest/gtest.h>

#include <AllegroFlare/SegmentInfo3D.hpp>


TEST(AllegroFlare_SegmentInfo3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SegmentInfo3D segment_info3d;
}


TEST(AllegroFlare_SegmentInfo3DTest, run__returns_the_expected_response)
{
   AllegroFlare::SegmentInfo3D segment_info3d;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, segment_info3d.run());
}


