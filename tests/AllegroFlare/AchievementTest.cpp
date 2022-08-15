


#include <gtest/gtest.h>

#include <AllegroFlare/Achievement.hpp>


TEST(AllegroFlare_AchievementTest, can_be_created_without_arguments)
{
   AllegroFlare::Achievement achievement;
}


TEST(AllegroFlare_AchievementTest, unlocked__is_initialized_to_false)
{
   AllegroFlare::Achievement achievement;
   EXPECT_EQ(false, achievement.is_unlocked());
}


TEST(AllegroFlare_AchievementTest, title__has_the_expected_default_value)
{
   AllegroFlare::Achievement achievement;
   EXPECT_EQ("Base", achievement.get_title());
}


TEST(AllegroFlare_AchievementTest, title__has_getters_and_setters_with_the_expected_behavior)
{
   AllegroFlare::Achievement achievement;
   achievement.set_title("My Achievement");
   EXPECT_EQ("My Achievement", achievement.get_title());
}


TEST(AllegroFlare_AchievementTest, title__is_set_on_construction)
{
   AllegroFlare::Achievement achievement("My Achievement");
   EXPECT_EQ("My Achievement", achievement.get_title());
}


TEST(AllegroFlare_AchievementTest, unlock_manually__will_unlock_the_achievement_and_return_true)
{
   AllegroFlare::Achievement achievement;
   EXPECT_EQ(true, achievement.unlock_manually());
   EXPECT_EQ(true, achievement.is_unlocked());
}


TEST(AllegroFlare_AchievementTest, unlock_manually__will_call_the_achievements_on_unlocked_method)
{
   // TODO: this test
}


TEST(AllegroFlare_AchievementTest, unlock_manually__if_already_unlocked__will_do_nothing_and_return_false)
{
   AllegroFlare::Achievement achievement;
   EXPECT_EQ(true, achievement.unlock_manually());
   EXPECT_EQ(false, achievement.unlock_manually());
}


