
#include <gtest/gtest.h>

#include <AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect.hpp>


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapWithZoomEffectTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect smooth_snap_with_zoom_effect;
}


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapWithZoomEffectTest, TYPE__has_the_expected_value)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect smooth_snap_with_zoom_effect;
   std::string expected_type = "AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect";
   EXPECT_EQ(expected_type, smooth_snap_with_zoom_effect.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_SmoothSnapWithZoomEffectTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect smooth_snap_with_zoom_effect;
   EXPECT_EQ(AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::TYPE, smooth_snap_with_zoom_effect.get_type());
}


