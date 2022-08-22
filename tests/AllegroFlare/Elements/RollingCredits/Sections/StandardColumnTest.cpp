
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/StandardColumn.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_StandardColumnTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::StandardColumn standard_column;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_StandardColumnTest, has_the_expected_type)
{
   AllegroFlare::Elements::RollingCredits::Sections::StandardColumn standard_column;
   EXPECT_EQ("StandardColumn", standard_column.get_type());
}


