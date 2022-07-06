
#include <gtest/gtest.h>

#include <AllegroFlare/TimeStamper.hpp>


TEST(AllegroFlare_TimeStamperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TimeStamper time_stamper;
}


TEST(AllegroFlare_TimeStamperTest, run__returns_the_expected_response)
{
   AllegroFlare::TimeStamper time_stamper;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, time_stamper.generate_now_timestamp_utc());
}

