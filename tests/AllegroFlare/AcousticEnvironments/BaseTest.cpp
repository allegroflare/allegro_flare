
#include <gtest/gtest.h>

#include <AllegroFlare/AcousticEnvironments/Base.hpp>


class AcousticEnvironmentsBaseTestClass : public AllegroFlare::AcousticEnvironments::Base
{
public:
   AcousticEnvironmentsBaseTestClass()
      : AllegroFlare::AcousticEnvironments::Base("AcousticEnvironmentsBaseTestClass")
   {}
};


TEST(AllegroFlare_AcousticEnvironments_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::AcousticEnvironments::Base base;
}


TEST(AllegroFlare_AcousticEnvironments_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::AcousticEnvironments::Base base;
   EXPECT_EQ("AcousticEnvironments/Base", base.get_type());
}


TEST(AllegroFlare_AcousticEnvironments_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::AcousticEnvironments::Base base;
   EXPECT_EQ(AllegroFlare::AcousticEnvironments::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_AcousticEnvironments_BaseTest, derived_classes_will_have_the_expected_type)
{
   AcousticEnvironmentsBaseTestClass test_class;
   EXPECT_EQ("AcousticEnvironmentsBaseTestClass", test_class.get_type());
}


