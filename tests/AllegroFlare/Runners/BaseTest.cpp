
#include <gtest/gtest.h>

#include <AllegroFlare/Runners/Base.hpp>


class RunnersBaseTestClass : public AllegroFlare::Runners::Base
{
public:
   RunnersBaseTestClass()
      : AllegroFlare::Runners::Base("RunnersBaseTestClass")
   {}
};


TEST(AllegroFlare_Runners_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Runners::Base base;
}


TEST(AllegroFlare_Runners_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Runners/Base",
     AllegroFlare::Runners::Base::TYPE
   );
}


TEST(AllegroFlare_Runners_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Runners::Base base;
   EXPECT_EQ(AllegroFlare::Runners::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Runners_BaseTest, derived_classes_will_have_the_expected_type)
{
   RunnersBaseTestClass test_class;
   EXPECT_EQ("RunnersBaseTestClass", test_class.get_type());
}


