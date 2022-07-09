
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>


TEST(AllegroFlare_Elements_StoryboardPages_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Base base;
}


TEST(AllegroFlare_Elements_StoryboardPages_BaseTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(AllegroFlare_Elements_StoryboardPages_BaseTest, finished__is_initialized_to_true)
{
   AllegroFlare::Elements::StoryboardPages::Base base;
   EXPECT_EQ(true, base.get_finished());
}


