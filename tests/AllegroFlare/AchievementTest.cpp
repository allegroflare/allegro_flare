


#include <gtest/gtest.h>

#include <AllegroFlare/Achievement.hpp>


TEST(AllegroFlare_AchievementTest, can_be_created_without_arguments)
{
   AllegroFlare::Achievement achievements;
}


TEST(AllegroFlare_AchievementTest, unlocked__is_initialized_to_false)
{
   AllegroFlare::Achievement achievements;
   EXPECT_EQ(false, achievements.is_unlocked());
}


TEST(AllegroFlare_AchievementTest, unlock_manually__will_unlock_the_achievement_and_return_true)
{
   AllegroFlare::Achievement achievements;
   EXPECT_EQ(true, achievements.unlock_manually());
   EXPECT_EQ(true, achievements.is_unlocked());
}


TEST(AllegroFlare_AchievementTest, unlock_manually__will_call_the_achievements_on_unlocked_method)
{
   // TODO: this test
}


TEST(AllegroFlare_AchievementTest, unlock_manually__if_already_unlocked__will_do_nothing_and_return_false)
{
   AllegroFlare::Achievement achievements;
   EXPECT_EQ(true, achievements.unlock_manually());
   EXPECT_EQ(false, achievements.unlock_manually());
}


