
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/TimeStamper.hpp>


// Helper function to manually construct the expected format
static std::string expected_iso_format(int year, int month, int day, int hour, int min, int sec, const std::string &tz)
{
   char buffer[30];
   std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02dT%02d:%02d:%02d%s",
                 year, month, day, hour, min, sec, tz.c_str());
   return std::string(buffer);
}


TEST(AllegroFlare_TimeStamperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TimeStamper time_stamper;
}


TEST(AllegroFlare_TimeStamperTest, create_local_time_now__will_produce_the_current_time)
{
   // TODO: Figure out how to test this
   std::tm time_now = AllegroFlare::TimeStamper::create_local_time_now();
}


TEST(AllegroFlare_TimeStamperTest, to_iso_8601_time_str__will_convert_the_time_to_the_expected_format__leap_year)
{
   // Test Leap Year Date: Feb 29, 2024
   std::tm test_time{};
   test_time.tm_year = 2024 - 1900; // tm_year is years since 1900
   test_time.tm_mon = 1;  // February (0-based)
   test_time.tm_mday = 29;
   test_time.tm_hour = 12;
   test_time.tm_min = 34;
   test_time.tm_sec = 56;

   std::string result = AllegroFlare::TimeStamper::to_iso_8601_time_str(&test_time);
   std::string expected = expected_iso_format(2024, 2, 29, 12, 34, 56, "+00:00"); // Adjust timezone manually if needed

   EXPECT_EQ(result.substr(0, 19), expected.substr(0, 19)); // Check date and time format
   EXPECT_THAT(result[19], ::testing::AnyOf('+', '-')); // Allow either '+' or '-'
}


TEST(AllegroFlare_TimeStamperTest, to_iso_8601_time_str__will_convert_the_time_to_the_expected_format__new_year)
{
   // Test New Year's Transition: Dec 31, 2023 ? Jan 1, 2024
   std::tm test_time{};
   test_time.tm_year = 2023 - 1900;
   test_time.tm_mon = 11; // December
   test_time.tm_mday = 31;
   test_time.tm_hour = 23;
   test_time.tm_min = 59;
   test_time.tm_sec = 59;

   std::string result = AllegroFlare::TimeStamper::to_iso_8601_time_str(&test_time);
   std::string expected = expected_iso_format(2023, 12, 31, 23, 59, 59, "+00:00");

   EXPECT_EQ(result.substr(0, 19), expected.substr(0, 19));
   EXPECT_THAT(result[19], ::testing::AnyOf('+', '-')); // Allow either '+' or '-'
}


TEST(AllegroFlare_TimeStamperTest, to_iso_8601_time_str__will_convert_the_time_to_the_expected_format__daylight_savings)
{
   // Test Daylight Saving Time Start: US Eastern Time (DST begins at 2 AM)
   std::tm test_time{};
   test_time.tm_year = 2024 - 1900;
   test_time.tm_mon = 2; // March
   test_time.tm_mday = 10;
   test_time.tm_hour = 2;
   test_time.tm_min = 30;
   test_time.tm_sec = 0;

   std::string result = AllegroFlare::TimeStamper::to_iso_8601_time_str(&test_time);
   std::string expected = expected_iso_format(2024, 3, 10, 2, 30, 0, "+00:00"); // Adjust timezone manually

   EXPECT_EQ(result.substr(0, 19), expected.substr(0, 19));
   EXPECT_THAT(result[19], ::testing::AnyOf('+', '-')); // Allow either '+' or '-'
}


TEST(AllegroFlare_TimeStamperTest,
   DISABLED_to_iso_8601_time_str__will_respect_the_time_zone_obtained_by_create_local_time_now)
{
   std::tm test_time = AllegroFlare::TimeStamper::create_local_time_now();
   std::string result = AllegroFlare::TimeStamper::to_iso_8601_time_str(&test_time);
   std::string expected = expected_iso_format(2025, 3, 10, 2, 30, 0, "+00:00"); // Adjust timezone manually
   EXPECT_EQ("2025-03-10T23:02:12-04:00", result);
}


