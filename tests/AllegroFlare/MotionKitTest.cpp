
#include <gtest/gtest.h>

#include <AllegroFlare/MotionKit.hpp>


TEST(AllegroFlare_MotionKitTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionKit motion_kit;
}


TEST(AllegroFlare_MotionKitTestWithAllegroRenderingFixture, calc_normalized_age__will_return_the_expected_values)
{
   float expected = 0.5f;
   float actual = AllegroFlare::MotionKit::normalize_age(0.0, 2.0, 1.0);
   EXPECT_EQ(expected, actual);
}


TEST(AllegroFlare_MotionKitTestWithAllegroRenderingFixture, interpolate__will_return_the_expected_values)
{
   float expected = -9.5f;
   float actual = AllegroFlare::MotionKit::interpolate(1.0, -20.0, 0.5);
   EXPECT_EQ(expected, actual);
}


