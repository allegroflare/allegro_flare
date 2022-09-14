
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>


TEST(AllegroFlare_Prototypes_MindDive_MindDiveTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive;
}


TEST(AllegroFlare_Prototypes_MindDive_MindDiveTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, mind_dive.run());
}


