
#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/String.hpp>


TEST(AllegroFlare_GameEventDatas_StringTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::String string;
}


TEST(AllegroFlare_GameEventDatas_StringTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameEventDatas/String",
     AllegroFlare::GameEventDatas::String::TYPE
   );
}


TEST(AllegroFlare_GameEventDatas_StringTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::String string;
   EXPECT_EQ(AllegroFlare::GameEventDatas::String::TYPE, string.get_type());
}


