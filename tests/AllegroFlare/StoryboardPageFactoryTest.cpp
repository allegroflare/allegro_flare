
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_StoryboardPageFactoryTest : public ::testing::Test
{};

class AllegroFlare_StoryboardPageFactoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/StoryboardPageFactory.hpp>


TEST_F(AllegroFlare_StoryboardPageFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StoryboardPageFactory storyboard_factory;
}


TEST_F(AllegroFlare_StoryboardPageFactoryTestWithAllegroRenderingFixture,
   create_text_page__will_create_the_text_page_with_the_expected_params)
{
   AllegroFlare::StoryboardPageFactory storyboard_factory(&get_font_bin_ref());
   AllegroFlare::Elements::StoryboardPages::Text* created_page = storyboard_factory.create_text_page("Hello Factory!");

   EXPECT_EQ(&get_font_bin_ref(), created_page->get_font_bin());
   EXPECT_EQ("Hello Factory!", created_page->get_text());
}


TEST_F(AllegroFlare_StoryboardPageFactoryTestWithAllegroRenderingFixture,
   create_advancing_text_page__will_create_the_text_page_with_the_expected_params)
{
   AllegroFlare::StoryboardPageFactory storyboard_factory(&get_font_bin_ref());
   AllegroFlare::Elements::StoryboardPages::AdvancingText* created_page =
      storyboard_factory.create_advancing_text_page("Hello Factory!");

   EXPECT_EQ(&get_font_bin_ref(), created_page->get_font_bin());
   EXPECT_EQ("Hello Factory!", created_page->get_text());
}


TEST_F(AllegroFlare_StoryboardPageFactoryTestWithAllegroRenderingFixture,
   create_image_page__will_create_an_image_page_with_the_expected_params)
{
   // TODO
}


