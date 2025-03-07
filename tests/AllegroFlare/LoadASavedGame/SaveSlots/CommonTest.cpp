
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>


TEST(AllegroFlare_LoadASavedGame_SaveSlots_CommonTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Common common;
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_CommonTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/LoadASavedGame/SaveSlots/Common",
     AllegroFlare::LoadASavedGame::SaveSlots::Common::TYPE
   );
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_CommonTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Common save_slot;
   EXPECT_EQ(AllegroFlare::LoadASavedGame::SaveSlots::Common::TYPE, save_slot.get_type());
}


