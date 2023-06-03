
#include <gtest/gtest.h>

#include <AllegroFlare/RouteEventDatas/ActivateScreen.hpp>


TEST(AllegroFlare_RouteEventDatas_ActivateScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RouteEventDatas::ActivateScreen activate_screen;
}


TEST(AllegroFlare_RouteEventDatas_ActivateScreenTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/RouteEventDatas/ActivateScreen",
     AllegroFlare::RouteEventDatas::ActivateScreen::TYPE
   );
}


