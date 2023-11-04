
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/SaveSlots/Basic.hpp>


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Basic basic;
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BasicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/LoadASavedGame/SaveSlots/Basic",
     AllegroFlare::LoadASavedGame::SaveSlots::Basic::TYPE
   );
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_BasicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Basic basic;
   EXPECT_EQ(AllegroFlare::LoadASavedGame::SaveSlots::Basic::TYPE, basic.get_type());
}


