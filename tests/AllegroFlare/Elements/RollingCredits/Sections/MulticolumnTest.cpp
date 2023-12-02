
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::Multicolumn multicolumn;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/RollingCredits/Sections/Multicolumn",
     AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE
   );
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_MulticolumnTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::Sections::Multicolumn multicolumn;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE, multicolumn.get_type());
}


