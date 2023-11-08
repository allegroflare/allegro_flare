


#include <gtest/gtest.h>

#include <AllegroFlare/Achievements.hpp>


class AchievementTestClass : public AllegroFlare::Achievement
{};


TEST(AllegroFlare_AchievementsTest, can_be_created_without_arguments)
{
   AllegroFlare::Achievements achievements;
}


TEST(AllegroFlare_AchievementsTest, add__will_add_the_achievement_to_the_list)
{
   AllegroFlare::Achievements achievements;
   AchievementTestClass achievement;

   achievements.add("my_achievement", &achievement);

   std::string expected_dump_string = "achievement: \"my_achievement\", unlocked: false\n";
   std::string actual_dump_string = achievements.dump();
   EXPECT_EQ(expected_dump_string, actual_dump_string);
}


TEST(AllegroFlare_AchievementsTest,
   unlock_manually__will_mark_the_achievement_as_unlocked_in_the_list_and_on_the_object_and_return_true)
{
   AllegroFlare::Achievements achievements;
   AchievementTestClass achievement;
   achievements.add("my_achievement", &achievement);

   EXPECT_EQ(true, achievements.unlock_manually("my_achievement"));

   std::string expected_dump_string = "achievement: \"my_achievement\", unlocked: true\n";
   std::string actual_dump_string = achievements.dump();
   EXPECT_EQ(expected_dump_string, actual_dump_string);
}


TEST(AllegroFlare_AchievementsTest,
   DISABLED__unlock_manually__will_emit_an_ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED_event)
{
   // TODO: This test
   //AllegroFlare::Achievements achievements;
   //AchievementTestClass achievement;
   //achievements.add("my_achievement", &achievement);

   //EXPECT_EQ(true, achievements.unlock_manually("my_achievement"));

   //std::string expected_dump_string = "achievement: \"my_achievement\", unlocked: true\n";
   //std::string actual_dump_string = achievements.dump();
   //EXPECT_EQ(expected_dump_string, actual_dump_string);
}


TEST(AllegroFlare_AchievementsTest,
   unlock_manually__when_the_achievement_identifier_does_not_exist__will_output_an_error_message_to_cout)
{
   AllegroFlare::Achievements achievements;
   testing::internal::CaptureStdout();

   achievements.unlock_manually("an-achievement-identifier-that-does-not-exist");

   std::string expected_cout_output = "[Achievements::unlock_manually] error: Could not find "
                                      "achievement with identifier \"an-achievement-identifier-that-does-not-exist\"";
   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(expected_cout_output, actual_cout_output);
}


TEST(AllegroFlare_AchievementsTest,
   unlock_manually__when_the_achievement_has_already_been_unlocked__does_nothing_and_returns_false)
{
   AllegroFlare::Achievements achievements;
   AchievementTestClass achievement;
   achievements.add("my_achievement", &achievement);

   achievements.unlock_manually("my_achievement");
   EXPECT_EQ(false, achievements.unlock_manually("my_achievement"));
}


TEST(AllegroFlare_AchievementsTest,
   unlock_silently__will_mark_the_achievement_as_unlocked_in_the_list_and_on_the_object_and_return_true)
{
   AllegroFlare::Achievements achievements;
   AchievementTestClass achievement;
   achievements.add("my_achievement", &achievement);

   EXPECT_EQ(true, achievements.unlock_silently("my_achievement"));

   std::string expected_dump_string = "achievement: \"my_achievement\", unlocked: true\n";
   std::string actual_dump_string = achievements.dump();
   EXPECT_EQ(expected_dump_string, actual_dump_string);
}


TEST(AllegroFlare_AchievementsTest,
   unlock_silently__when_the_achievement_identifier_does_not_exist__will_output_an_error_message_to_cout)
{
   AllegroFlare::Achievements achievements;
   testing::internal::CaptureStdout();

   achievements.unlock_silently("an-achievement-identifier-that-does-not-exist");

   std::string expected_cout_output = "[Achievements::unlock_silently] error: Could not find "
                                      "achievement with identifier \"an-achievement-identifier-that-does-not-exist\"";
   std::string actual_cout_output = testing::internal::GetCapturedStdout();
   EXPECT_EQ(expected_cout_output, actual_cout_output);
}


TEST(AllegroFlare_AchievementsTest,
   unlock_silently__when_the_achievement_has_already_been_unlocked__does_nothing_and_returns_false)
{
   AllegroFlare::Achievements achievements;
   AchievementTestClass achievement;
   achievements.add("my_achievement", &achievement);

   achievements.unlock_silently("my_achievement");
   EXPECT_EQ(false, achievements.unlock_silently("my_achievement"));
}


TEST(AllegroFlare_AchievementsTest,
   DISABLED__unlock_silently__will_not_emit_an_ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED_event)
{
   // TODO: This test
   //AllegroFlare::Achievements achievements;
   //AchievementTestClass achievement;
   //achievements.add("my_achievement", &achievement);

   //EXPECT_EQ(true, achievements.unlock_silently("my_achievement"));

   //std::string expected_dump_string = "achievement: \"my_achievement\", unlocked: true\n";
   //std::string actual_dump_string = achievements.dump();
   //EXPECT_EQ(expected_dump_string, actual_dump_string);
}


