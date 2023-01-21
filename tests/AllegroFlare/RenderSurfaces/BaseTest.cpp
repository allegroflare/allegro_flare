
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/Base.hpp>


class RenderSurfacesBaseTestClass : public AllegroFlare::RenderSurfaces::Base
{
public:
   RenderSurfacesBaseTestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBaseTestClass")
   {}
};


TEST(AllegroFlare_RenderSurfaces_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RenderSurfaces::Base base;
}


TEST(AllegroFlare_RenderSurfaces_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::RenderSurfaces::Base base;
   EXPECT_EQ("RenderSurfaces/Base", base.get_type());
}


TEST(AllegroFlare_RenderSurfaces_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RenderSurfaces::Base base;
   EXPECT_EQ(AllegroFlare::RenderSurfaces::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_RenderSurfaces_BaseTest, derived_classes_will_have_the_expected_type)
{
   RenderSurfacesBaseTestClass test_class;
   EXPECT_EQ("RenderSurfacesBaseTestClass", test_class.get_type());
}


