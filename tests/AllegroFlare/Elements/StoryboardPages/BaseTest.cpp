
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>


TEST(AllegroFlare_Elements_StoryboardPages_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Base base;
}


TEST(AllegroFlare_Elements_StoryboardPages_BaseTest, run__returns_the_expected_response)
{
   AllegroFlare::Elements::StoryboardPages::Base base;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, base.run());
}

