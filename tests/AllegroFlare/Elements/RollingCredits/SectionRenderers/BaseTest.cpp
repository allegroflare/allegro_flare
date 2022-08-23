
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Base.hpp>


class BaseTestClass : public AllegroFlare::Elements::RollingCredits::SectionRenderers::Base
{
public:
   BaseTestClass()
      : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base("BaseTestClass")
   {}
};


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Base base;
}


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_BaseTest, has_the_expected_type)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(AllegroFlare_Elements_RollingCredits_SectionRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   BaseTestClass test_class;
   EXPECT_EQ("BaseTestClass", test_class.get_type());
}


