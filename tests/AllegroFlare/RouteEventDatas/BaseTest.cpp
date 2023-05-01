
#include <gtest/gtest.h>

#include <AllegroFlare/RouteEventDatas/Base.hpp>


class RouteEventDatasBaseTestClass : public AllegroFlare::RouteEventDatas::Base
{
public:
   RouteEventDatasBaseTestClass()
      : AllegroFlare::RouteEventDatas::Base("RouteEventDatasBaseTestClass")
   {}
};


TEST(AllegroFlare_RouteEventDatas_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RouteEventDatas::Base base;
}


TEST(AllegroFlare_RouteEventDatas_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/RouteEventDatas/Base",
     AllegroFlare::RouteEventDatas::Base::TYPE
   );
}


TEST(AllegroFlare_RouteEventDatas_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RouteEventDatas::Base base;
   EXPECT_EQ(AllegroFlare::RouteEventDatas::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_RouteEventDatas_BaseTest, derived_classes_will_have_the_expected_type)
{
   RouteEventDatasBaseTestClass test_class;
   EXPECT_EQ("RouteEventDatasBaseTestClass", test_class.get_type());
}


