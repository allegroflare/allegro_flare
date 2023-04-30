
#include <gtest/gtest.h>

#include <AllegroFlare/Routers/Base.hpp>


class RoutersBaseTestClass : public AllegroFlare::Routers::Base
{
public:
   RoutersBaseTestClass()
      : AllegroFlare::Routers::Base("RoutersBaseTestClass")
   {}
};


TEST(AllegroFlare_Routers_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Routers::Base base;
}


TEST(AllegroFlare_Routers_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Routers/Base",
     AllegroFlare::Routers::Base::TYPE
   );
}


TEST(AllegroFlare_Routers_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Routers::Base base;
   EXPECT_EQ(AllegroFlare::Routers::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Routers_BaseTest, derived_classes_will_have_the_expected_type)
{
   RoutersBaseTestClass test_class;
   EXPECT_EQ("RoutersBaseTestClass", test_class.get_type());
}


