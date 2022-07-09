
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>


TEST(AllegroFlare_Elements_StoryboardPages_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
}


TEST(AllegroFlare_Elements_StoryboardPages_TextTest, run__returns_the_expected_response)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, text.run());
}

