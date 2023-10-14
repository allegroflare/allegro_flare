
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable.hpp>


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelUnlockableTest,
      can_be_created_without_blowing_up
   )
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable thumbnail_with_label_unlockable;
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelUnlockableTest,
      TYPE__has_the_expected_value
   )
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabelUnlockable",
     AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE
   );
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_ThumbnailWithLabelUnlockableTest,
      type__has_the_expected_value_matching_TYPE
   )
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable thumbnail_with_label_unlockable;
   EXPECT_EQ(AllegroFlare::Elements::ChapterSelect::CarouselElements::ThumbnailWithLabelUnlockable::TYPE, thumbnail_with_label_unlockable.get_type());
}


