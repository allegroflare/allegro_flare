
#include <gtest/gtest.h>

#include <AllegroFlare/CameraControlStrategies2D/Snap.hpp>


TEST(AllegroFlare_CameraControlStrategies2D_SnapTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CameraControlStrategies2D::Snap snap;
}


TEST(AllegroFlare_CameraControlStrategies2D_SnapTest, TYPE__has_the_expected_value)
{
   AllegroFlare::CameraControlStrategies2D::Snap snap;
   EXPECT_EQ("AllegroFlare/CameraControlStrategies2D/Snap", snap.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_SnapTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::CameraControlStrategies2D::Snap snap;
   EXPECT_EQ(AllegroFlare::CameraControlStrategies2D::Snap::TYPE, snap.get_type());
}


