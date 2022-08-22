
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>


class BaseTestClass : public AllegroFlare::Elements::RollingCredits::Sections::Base
{
public:
   BaseTestClass()
      : AllegroFlare::Elements::RollingCredits::Sections::Base("BaseTestClass")
   {}
};


TEST(AllegroFlare_Elements_RollingCredits_Sections_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Base base;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_BaseTest, has_the_expected_type)
{
   AllegroFlare::Elements::RollingCredits::Sections::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_BaseTest, derived_classes_will_have_the_expected_type)
{
   BaseTestClass test_class;
   EXPECT_EQ("BaseTestClass", test_class.get_type());
}


