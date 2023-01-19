
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Base.hpp>


class ShadersBaseTestClass : public AllegroFlare::Shaders::Base
{
public:
   ShadersBaseTestClass()
      : AllegroFlare::Shaders::Base("ShadersBaseTestClass")
   {}
};


TEST(AllegroFlare_Shaders_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::Base base;
}


TEST(AllegroFlare_Shaders_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::Base base;
   EXPECT_EQ("AllegroFlare/Shaders/Base", base.get_type());
}


TEST(AllegroFlare_Shaders_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::Base base;
   EXPECT_EQ(AllegroFlare::Shaders::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Shaders_BaseTest, derived_classes_will_have_the_expected_type)
{
   ShadersBaseTestClass test_class;
   EXPECT_EQ("ShadersBaseTestClass", test_class.get_type());
}


