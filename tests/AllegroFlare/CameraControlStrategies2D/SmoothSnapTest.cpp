
#include <gtest/gtest.h>

#include <AllegroFlare/CameraControlStrategies2D/SmoothSnap.hpp>


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnap smooth_snap;
}


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnap smooth_snap;
   EXPECT_EQ("AllegroFlare/CameraControlStrategies2D/SmoothSnap", smooth_snap.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnap smooth_snap;
   EXPECT_EQ(AllegroFlare::CameraControlStrategies2D::SmoothSnap::TYPE, smooth_snap.get_type());
}


