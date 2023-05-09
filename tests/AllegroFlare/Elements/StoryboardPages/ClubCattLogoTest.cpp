
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>


TEST(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::ClubCattLogo club_catt_logo;
}


TEST(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/StoryboardPages/ClubCattLogo",
     AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE
   );
}


TEST(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::StoryboardPages::ClubCattLogo club_catt_logo;
   EXPECT_EQ(AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE, club_catt_logo.get_type());
}


