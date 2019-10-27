

#include <gtest/gtest.h>

#include <AllegroFlare/TimerFormatter.hpp>


using namespace AllegroFlare;


TEST(AllegroFlare_TimerFormatterTest, can_be_created_without_arguments)
{
   TimerFormatter formatter;
}


int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


