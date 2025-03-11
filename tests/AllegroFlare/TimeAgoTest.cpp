
#include <gtest/gtest.h>

#include <AllegroFlare/TimeAgo.hpp>


TEST(AllegroFlare_TimeAgoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TimeAgo time_ago;
}


TEST(AllegroFlare_TimeAgoTest, time_ago__will_produce_a_time_string_of_the_distance_between_times__1)
{
   std::tm time_now = AllegroFlare::TimeAgo::create_local_time_now();
   std::tm time_past = time_now;
   time_past.tm_min -= 2;
   //std::mktime(&time_past); // Normalize the time

   std::string expected_time_ago = "2 minutes ago";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(&time_past, &time_now);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}


TEST(AllegroFlare_TimeAgoTest, time_ago__will_produce_a_time_string_of_the_distance_between_times__2)
{
   std::tm time_now = AllegroFlare::TimeAgo::create_local_time_now();
   std::tm time_past = time_now;
   time_past.tm_hour -= 3;
   //std::mktime(&time_past); // Normalize the time

   std::string expected_time_ago = "3 hours ago";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(&time_past, &time_now);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}


TEST(AllegroFlare_TimeAgoTest, time_ago__will_produce_a_time_string_of_the_distance_between_times__3)
{
   std::tm time_now = AllegroFlare::TimeAgo::create_local_time_now();
   std::tm time_past = time_now;
   time_past.tm_year -= 2;
   //std::mktime(&time_past); // Normalize the time

   std::string expected_time_ago = "2 years ago";
   std::string actual_time_ago = AllegroFlare::TimeAgo::time_ago(&time_past, &time_now);
   EXPECT_EQ(expected_time_ago, actual_time_ago);
}


