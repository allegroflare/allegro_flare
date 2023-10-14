#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/ChapterSelect/ChapterSelect.hpp>
#include <AllegroFlare/Elements/ChapterSelect/CarouselElements/ThumbnailWithLabel.hpp>


class AllegroFlare_Elements_ChapterSelect_ChapterSelectTest : public ::testing::Test {};
class AllegroFlare_Elements_ChapterSelect_ChapterSelectTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_ChapterSelect_ChapterSelectTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ChapterSelect::ChapterSelect chapter_select;
}


TEST_F(AllegroFlare_Elements_ChapterSelect_ChapterSelectTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   using namespace AllegroFlare::Elements::ChapterSelect::CarouselElements;

   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::Elements::ChapterSelect::ChapterSelect chapter_select;
   chapter_select.set_event_emitter(&event_emitter);
   chapter_select.set_bitmap_bin(&get_bitmap_bin_ref());
   chapter_select.set_font_bin(&get_font_bin_ref());
   chapter_select.initialize();

   std::vector<AllegroFlare::Elements::ChapterSelect::CarouselElements::Base*> carousel_elements = {
      //new ThumbnailWithLabel("scene1-01.jpg", "CHAPTER 1: Rise of the City"),
      //new ThumbnailWithLabel("scene2-01.jpg", "CHAPTER 2: The Sanctuary"),
      //new ThumbnailWithLabel("scene1-01.jpg", "CHAPTER 1: Rise of the City"),
      //new ThumbnailWithLabel("scene2-01.jpg", "CHAPTER 2: The Sanctuary"),
      new ThumbnailWithLabel("storyboard-image-1164x500.png", "CHAPTER 1: Rise of the City"),
      new ThumbnailWithLabel("storyboard-image-1164x500.png", "CHAPTER 2: The Sanctuary"),
      new ThumbnailWithLabel("storyboard-image-1164x500.png", "CHAPTER 3: The Bridge"),
   };

   chapter_select.set_carousel_elements(carousel_elements);

   clear();
   chapter_select.render();
   al_flip_display();
   al_rest(1);
}


