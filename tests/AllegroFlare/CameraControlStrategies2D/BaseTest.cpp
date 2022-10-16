
#include <gtest/gtest.h>

#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>


class CameraControlStrategies2DBaseTestClass : public AllegroFlare::CameraControlStrategies2D::Base
{
public:
   CameraControlStrategies2DBaseTestClass()
      : AllegroFlare::CameraControlStrategies2D::Base("CameraControlStrategies2DBaseTestClass")
   {}
};


TEST(AllegroFlare_CameraControlStrategies2D_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CameraControlStrategies2D::Base base;
}


TEST(AllegroFlare_CameraControlStrategies2D_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::CameraControlStrategies2D::Base base;
   EXPECT_EQ("AllegroFlare/CameraControlStrategies2D/Base", base.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::CameraControlStrategies2D::Base base;
   EXPECT_EQ(AllegroFlare::CameraControlStrategies2D::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_CameraControlStrategies2D_BaseTest, derived_classes_will_have_the_expected_type)
{
   CameraControlStrategies2DBaseTestClass test_class;
   EXPECT_EQ("CameraControlStrategies2DBaseTestClass", test_class.get_type());
}


