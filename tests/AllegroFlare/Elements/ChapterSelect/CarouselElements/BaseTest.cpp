
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/Base.hpp>


class CarouselElementsBaseTestClass : public AllegroFlare::Elements::ChapterSelect::CarouselElements::Base
{
public:
   CarouselElementsBaseTestClass()
      : AllegroFlare::Elements::ChapterSelect::CarouselElements::Base("CarouselElementsBaseTestClass")
   {}
};


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::Base base;
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/ChapterSelect/CarouselElements/Base",
     AllegroFlare::Elements::ChapterSelect::CarouselElements::Base::TYPE
   );
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElements::Base base;
   EXPECT_EQ(AllegroFlare::Elements::ChapterSelect::CarouselElements::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElements_BaseTest, derived_classes_will_have_the_expected_type)
{
   CarouselElementsBaseTestClass test_class;
   EXPECT_EQ("CarouselElementsBaseTestClass", test_class.get_type());
}


