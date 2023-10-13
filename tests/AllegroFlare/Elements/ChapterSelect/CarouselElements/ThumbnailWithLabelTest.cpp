
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel thumbnail_with_label;
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel",
     AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE
   );
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel thumbnail_with_label;
   EXPECT_EQ(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabel::TYPE, thumbnail_with_label.get_type());
}


