
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Spacer.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_SpacerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Spacer spacer;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_SpacerTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/RollingCredits/Sections/Spacer",
     AllegroFlare::Elements::RollingCredits::Sections::Spacer::TYPE
   );
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_SpacerTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::Sections::Spacer spacer;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::Sections::Spacer::TYPE, spacer.get_type());
}


