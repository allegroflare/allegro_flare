
#include <gtest/gtest.h>

#include <AllegroFlare/PlaytimeTracker.hpp>


TEST(AllegroFlare_PlaytimeTrackerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PlaytimeTracker playtime_tracker;
}


TEST(AllegroFlare_PlaytimeTrackerTest, from_string__will_import_a_string_from_a_save_value)
{
   AllegroFlare::PlaytimeTracker playtime_tracker;
   playtime_tracker.from_string("837456");

   std::chrono::milliseconds expected_total_playtime(837456);
   std::chrono::milliseconds actual_total_playtime = playtime_tracker.calculate_total_playtime();

   EXPECT_EQ(expected_total_playtime, actual_total_playtime);
}


TEST(AllegroFlare_PlaytimeTrackerTest, to_string__will_output_the_current_total_playtime_to_a_string_for_saving)
{
   AllegroFlare::PlaytimeTracker playtime_tracker;
   playtime_tracker.from_string("837456");
   EXPECT_EQ("837456", playtime_tracker.to_string());
}


TEST(AllegroFlare_PlaytimeTrackerTest, formatted_current_total_playtime_hms__will_return_the_expected_formatted_string)
{
   AllegroFlare::PlaytimeTracker playtime_tracker;
   playtime_tracker.from_string("837456");

   std::string expected_time_str = "13m 57s";
   std::string actual_time_str = playtime_tracker.formatted_current_total_playtime_hms();
   EXPECT_EQ(expected_time_str, actual_time_str);
}


