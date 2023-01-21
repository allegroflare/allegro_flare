
#include <gtest/gtest.h>

#include <AllegroFlare/RenderSurfaces/Base.hpp>


class RenderSurfacesBaseTestClass : public AllegroFlare::RenderSurfaces::Base
{
public:
   RenderSurfacesBaseTestClass()
      : AllegroFlare::RenderSurfaces::Base("RenderSurfacesBaseTestClass")
   {}
   ~RenderSurfacesBaseTestClass() {};

   virtual bool set_as_target() override { return true; }
   virtual ALLEGRO_BITMAP* obtain_surface() override { return nullptr; }
   virtual int get_width() override { return 0; }
   virtual int get_height() override { return 0; }
};


TEST(AllegroFlare_RenderSurfaces_BaseTest, derived_classes_can_be_created_without_blowing_up)
{
   RenderSurfacesBaseTestClass test_class;
}


TEST(AllegroFlare_RenderSurfaces_BaseTest, derived_classes_will_have_the_expected_type)
{
   RenderSurfacesBaseTestClass test_class;
   EXPECT_EQ("RenderSurfacesBaseTestClass", test_class.get_type());
}


