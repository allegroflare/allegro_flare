
#include <gtest/gtest.h>

#include <AllegroFlare/RouteEventDatas/StartLevel.hpp>


TEST(AllegroFlare_RouteEventDatas_StartLevelTest, can_be_created_without_blowing_up)
{
   AllegroFlare::RouteEventDatas::StartLevel start_level;
}


TEST(AllegroFlare_RouteEventDatas_StartLevelTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/RouteEventDatas/StartLevel",
     AllegroFlare::RouteEventDatas::StartLevel::TYPE
   );
}


TEST(AllegroFlare_RouteEventDatas_StartLevelTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::RouteEventDatas::StartLevel start_level;
   EXPECT_EQ(AllegroFlare::RouteEventDatas::StartLevel::TYPE, start_level.get_type());
}


