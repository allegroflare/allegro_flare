

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


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


