
#include <gtest/gtest.h>

#include <AllegroFlare/CameraControlStrategies2D/HorizontalRail.hpp>


TEST(AllegroFlare_CameraControlStrategies2D_HorizontalRailTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CameraControlStrategies2D::HorizontalRail horizontal_rail;
}


TEST(AllegroFlare_CameraControlStrategies2D_HorizontalRailTest, TYPE__has_the_expected_value)
{
   AllegroFlare::CameraControlStrategies2D::HorizontalRail horizontal_rail;
   EXPECT_EQ("CameraControlStrategies2D/HorizontalRail", horizontal_rail.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_HorizontalRailTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::CameraControlStrategies2D::HorizontalRail horizontal_rail;
   EXPECT_EQ(AllegroFlare::CameraControlStrategies2D::HorizontalRail::TYPE, horizontal_rail.get_type());
}


