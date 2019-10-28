

#include <gtest/gtest.h>

#include <AllegroFlare/TimerFormatter.hpp>


using namespace AllegroFlare;


TEST(AllegroFlare_TimerFormatterTest, can_be_created_without_arguments)
{
   TimerFormatter formatter;
}


TEST(AllegroFlare_TimerFormatterTest, format__formats_the_milliseconds_to_the_expected_format)
{
   int milliseconds = 107289418;

   TimerFormatter formatter(milliseconds);

   std::string expected_format = "29:48:09.418";
   std::string actual_format = formatter.format();

   ASSERT_EQ(expected_format, actual_format);
}


TEST(AllegroFlare_TimerFormatterTest, format__with_no_hours_passed__formats_to_the_expected_format)
{
   TimerFormatter formatter(0);

   std::string expected_format = "00:00.000";
   std::string actual_format = formatter.format();

   ASSERT_EQ(expected_format, actual_format);
}


TEST(AllegroFlare_TimerFormatterTest, infer_hours_fragment__will_return_the_expected_hours_component)
{
   int milliseconds = 107289418;
   TimerFormatter formatter(milliseconds);

   std::string expected_hours_fragment = "29";
   std::string actual_hours_fragment = formatter.infer_hours_fragment();

   ASSERT_EQ(expected_hours_fragment, actual_hours_fragment);
}


TEST(AllegroFlare_TimerFormatterTest, infer_minutes_fragment__will_return_the_expected_minutes_component)
{
   int milliseconds = 107289418;
   TimerFormatter formatter(milliseconds);

   std::string expected_minutes_fragment = "48";
   std::string actual_minutes_fragment = formatter.infer_minutes_fragment();

   ASSERT_EQ(expected_minutes_fragment, actual_minutes_fragment);
}


TEST(AllegroFlare_TimerFormatterTest, infer_seconds_fragment__will_return_the_expected_seconds_component)
{
   int milliseconds = 107289418;
   TimerFormatter formatter(milliseconds);

   std::string expected_seconds_fragment = "09";
   std::string actual_seconds_fragment = formatter.infer_seconds_fragment();

   ASSERT_EQ(expected_seconds_fragment, actual_seconds_fragment);
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


