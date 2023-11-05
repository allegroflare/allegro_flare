
#include <gtest/gtest.h>

#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>


TEST(AllegroFlare_LoadASavedGame_SaveSlots_EmptyTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Empty empty;
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_EmptyTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/LoadASavedGame/SaveSlots/Empty",
     AllegroFlare::LoadASavedGame::SaveSlots::Empty::TYPE
   );
}


TEST(AllegroFlare_LoadASavedGame_SaveSlots_EmptyTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::LoadASavedGame::SaveSlots::Empty empty;
   EXPECT_EQ(AllegroFlare::LoadASavedGame::SaveSlots::Empty::TYPE, empty.get_type());
}


