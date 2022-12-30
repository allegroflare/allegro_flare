
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text text;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_TextTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text text;
   EXPECT_EQ("Sections/Text", text.get_type());
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_TextTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text text;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::Sections::Text::TYPE, text.get_type());
}


