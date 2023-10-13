#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>
#include <AllegroFlare/Elements/ChapterSelect/Carousel.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_ChapterSelect_CarouselTest : public ::testing::Test {};
class AllegroFlare_Elements_ChapterSelect_CarouselTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::Carousel carousel;
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::ChapterSelect::Carousel carousel(&get_bitmap_bin_ref(), &get_font_bin_ref());
   carousel.render();
}


TEST_F(AllegroFlare_Elements_ChapterSelect_CarouselTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_elements)
{
   using namespace AllegroFlare::Elements::ChapterSelect::CarouselElements;

   std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements = {
      new ThumbnailWithLabel("storyboard-image-1164x500.png", "CHAPTER 1: Rise of the City"),
      new ThumbnailWithLabel("storyboard-image-1164x500.png", "CHAPTER 2: The Sanctuary"),
   };

   // Fit the elements to their size
   for (auto &carousel_element : carousel_elements)
   {
      //carouse
      // ...
   }

   AllegroFlare::Elements::ChapterSelect::Carousel carousel(&get_bitmap_bin_ref(), &get_font_bin_ref());
   carousel.set_elements(carousel_elements);

   carousel.render();
   al_flip_display();
   sleep_for(1);
}


