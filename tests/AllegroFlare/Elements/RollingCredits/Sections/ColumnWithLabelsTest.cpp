
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>


TEST(AllegroFlare_Elements_RollingCredits_Sections_ColumnWithLabelsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels column_with_labels_section;
}


TEST(AllegroFlare_Elements_RollingCredits_Sections_ColumnWithLabelsTest, has_the_expected_type)
{
   AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels column_with_labels_section;
   EXPECT_EQ("StandardColumn", column_with_labels_section.get_type());
}


