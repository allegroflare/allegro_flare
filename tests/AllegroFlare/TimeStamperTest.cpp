
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/TimeStamper.hpp>


TEST(AllegroFlare_TimeStamperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TimeStamper time_stamper;
}


TEST(AllegroFlare_TimeStamperTest,
   DISABLED__generate_time_now_utc_iso8601__will_produce_the_current_time)
{
   // TODO: Figure out how to test this
   std::string expected_time_now = "2025-03-11T15:59:02Z";
   std::string actual_time_now = AllegroFlare::TimeStamper::generate_time_now_utc_iso8601();
   EXPECT_EQ(expected_time_now, actual_time_now);
}


TEST(AllegroFlare_TimeStamperTest, generate_time_now_since_epoch__will_produce_the_current_time)
{
   std::time_t expected_time_now = std::time(nullptr);
   std::time_t actual_time_now = AllegroFlare::TimeStamper::generate_time_now_since_epoch();
   EXPECT_EQ(expected_time_now, actual_time_now);
}


TEST(AllegroFlare_TimeStamperTest,
   FLAKEY__user_friendly_time__will_produce_a_string_of_the_time_since_epoch_in_the_users_local_time)
{
   std::time_t time_now = std::time(nullptr);
   std::cout << "Time now " << time_now << std::endl;

   std::string expected_time_now = "June 09 2025 04:20:28 PM";
   std::string actual_time_now = AllegroFlare::TimeStamper::user_friendly_time(time_now);
   EXPECT_EQ(expected_time_now, actual_time_now);
}


