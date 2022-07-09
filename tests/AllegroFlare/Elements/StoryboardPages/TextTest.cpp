
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>


TEST(AllegroFlare_Elements_StoryboardPages_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
}


TEST(AllegroFlare_Elements_StoryboardPages_TextTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   EXPECT_EQ("Text", text.get_type());
}


