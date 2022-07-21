
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/HealthBars/Hearts.hpp>


TEST(AllegroFlare_Elements_HealthBars_HeartsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::HealthBars::Hearts hearts;
}


TEST(AllegroFlare_Elements_HealthBars_HeartsTest, run__returns_the_expected_response)
{
   AllegroFlare::Elements::HealthBars::Hearts hearts;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, hearts.run());
}

