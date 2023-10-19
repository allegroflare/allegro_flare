
#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/ScreenActivated.hpp>


TEST(AllegroFlare_GameEventDatas_ScreenActivatedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::ScreenActivated screen_activated;
}


TEST(AllegroFlare_GameEventDatas_ScreenActivatedTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameEventDatas/ScreenActivated",
     AllegroFlare::GameEventDatas::ScreenActivated::TYPE
   );
}


TEST(AllegroFlare_GameEventDatas_ScreenActivatedTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::ScreenActivated screen_activated;
   EXPECT_EQ(AllegroFlare::GameEventDatas::ScreenActivated::TYPE, screen_activated.get_type());
}


