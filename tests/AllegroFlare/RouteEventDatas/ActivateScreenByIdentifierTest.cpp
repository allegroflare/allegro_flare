
#include <gtest/gtest.h>

#include <AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier.hpp>


TEST(AllegroFlare_RouteEventDatas_ActivateScreenByIdentifierTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier activate_screen;
}


TEST(AllegroFlare_RouteEventDatas_ActivateScreenByIdentifierTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier",
     AllegroFlare::RouteEventDatas::ActivateScreenByIdentifier::TYPE
   );
}


