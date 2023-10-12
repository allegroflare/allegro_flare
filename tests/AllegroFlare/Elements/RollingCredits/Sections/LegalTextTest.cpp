
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/LegalText.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_LegalTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::LegalText legal_text;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_LegalTextTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "Sections/LegalText", // TODO: Modify this to be "AllegroFlare/Elements/RollingCredits/Sections/LegalText"
     AllegroFlare::Elements::RollingCredits::Sections::LegalText::TYPE
   );
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_LegalTextTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::Sections::LegalText legal_text;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::Sections::LegalText::TYPE, legal_text.get_type());
}


