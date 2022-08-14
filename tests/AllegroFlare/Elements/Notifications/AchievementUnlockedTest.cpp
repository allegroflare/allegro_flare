
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Notifications/AchievementUnlocked.hpp>


TEST(AllegroFlare_Elements_Notifications_AchievementUnlockedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Notifications::AchievementUnlocked achievement_unlocked_notification;
}


TEST(AllegroFlare_Elements_Notifications_AchievementUnlockedTest, has_the_expected_type)
{
   AllegroFlare::Elements::Notifications::AchievementUnlocked achievement_unlocked_notification;
   EXPECT_EQ("AchievementUnlocked", achievement_unlocked_notification.get_type());
}


