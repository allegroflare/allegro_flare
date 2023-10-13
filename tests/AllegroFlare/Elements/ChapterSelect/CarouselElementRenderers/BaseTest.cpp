
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/Base.hpp>


class CarouselElementRenderersBaseTestClass : public AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base
{
public:
   CarouselElementRenderersBaseTestClass()
      : AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base("CarouselElementRenderersBaseTestClass")
   {}
};


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base base;
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/Base",
     AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base::TYPE
   );
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base base;
   EXPECT_EQ(AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Elements_ChapterSelect_CarouselElementRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   CarouselElementRenderersBaseTestClass test_class;
   EXPECT_EQ("CarouselElementRenderersBaseTestClass", test_class.get_type());
}


