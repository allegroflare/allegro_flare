
#include <gtest/gtest.h>

#include <AllegroFlare/TimeAgo.hpp>


TEST(AllegroFlare_TimeAgoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TimeAgo time_ago;
}


/*
TEST(AllegroFlare_TimeAgoTest, time_ago__will_produce_a_time_string_of_the_distance_between_times__1)
{
   std::time_t current_time = std::time(0);
   std::time_t past_time = current_time - (5 * 60 * 60 * 24); // 5 days ago for example
   std::string expected_time_ago = "5 days ago";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(past_time, current_time);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}


TEST(AllegroFlare_TimeAgoTest,
   time_ago__will_produce_a_time_string_of_the_distance_between_times__2)
{
   std::vector<std::pair<std::string, std::time_t>> test_data = {
      { "5 days ago",     (5 * 60 * 60 * 24) },
      { "2 months ago",   (2 * 30 * 60 * 60 * 24) }, // Approximate month as 30 days
      { "13 minutes ago", (13 * 60) },
      { "7 hours ago",    (7 * 60 * 60) },
      { "1 year ago",     (1 * 365 * 60 * 60 * 24) }, // Approximate year as 365 days
      { "45 seconds ago", 45 },
      { "Just now",       0 },
      { "Just now",       14 },
      { "15 seconds ago", 15 },
   };

   std::time_t current_time = std::time(0);
   for (auto &test_datum : test_data)
   {
      std::string expected_time_ago = test_datum.first;
      std::time_t past_time = current_time - test_datum.second;

      std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(past_time, current_time);
      EXPECT_EQ(expected_time_ago, actual_time_ago);
   }
}


TEST(AllegroFlare_TimeAgoTest,
   time_ago__will_produce_an_error_message_for_the_time_when_the_past_is_a_time_after_the_current_time__1)
{
   std::time_t current_time = std::time(0);
   std::time_t past_time = current_time + 60; // 1 minute

   std::string expected_time_ago = "Invalid time (future date)";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(past_time, current_time);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}


TEST(AllegroFlare_TimeAgoTest,
   time_ago__will_produce_an_error_message_for_the_time_when_the_past_is_a_time_after_the_current_time__2)
{
   std::time_t current_time = std::time(0);
   std::time_t past_time = current_time + 1; // 1 second

   std::string expected_time_ago = "Invalid time (future date)";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(past_time, current_time);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}
*/


