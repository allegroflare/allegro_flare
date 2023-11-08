
#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/AchievementUnlocked.hpp>


TEST(AllegroFlare_GameEventDatas_AchievementUnlockedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::AchievementUnlocked achievement_unlocked;
}


TEST(AllegroFlare_GameEventDatas_AchievementUnlockedTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GameEventDatas/AchievementUnlocked",
     AllegroFlare::GameEventDatas::AchievementUnlocked::TYPE
   );
}


TEST(AllegroFlare_GameEventDatas_AchievementUnlockedTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::AchievementUnlocked achievement_unlocked;
   EXPECT_EQ(AllegroFlare::GameEventDatas::AchievementUnlocked::TYPE, achievement_unlocked.get_type());
}


