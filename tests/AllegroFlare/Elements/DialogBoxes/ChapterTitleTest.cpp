
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/ChapterTitle.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_ChapterTitleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::ChapterTitle chapter_title;
}


TEST(AllegroFlare_Elements_DialogBoxes_ChapterTitleTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/ChapterTitle",
     AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_ChapterTitleTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::ChapterTitle chapter_title;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::ChapterTitle::TYPE, chapter_title.get_type());
}


