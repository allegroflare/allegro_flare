
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_StoryboardFactoryTest : public ::testing::Test
{};

class AllegroFlare_StoryboardFactoryTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/StoryboardFactory.hpp>


TEST_F(AllegroFlare_StoryboardFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StoryboardFactory storyboard_factory;
}


TEST_F(AllegroFlare_StoryboardFactoryTestWithAllegroRenderingFixture,
   create_text_page__will_create_the_text_page_with_the_expected_params)
{
   AllegroFlare::StoryboardFactory storyboard_factory(&get_font_bin_ref());
   AllegroFlare::Elements::StoryboardPages::Text* created_page = storyboard_factory.create_text_page("Hello Factory!");

   EXPECT_EQ(&get_font_bin_ref(), created_page->get_font_bin());
   EXPECT_EQ("Hello Factory!", created_page->get_text());
}


TEST_F(AllegroFlare_StoryboardFactoryTestWithAllegroRenderingFixture,
   create_advancing_text_page__will_create_the_text_page_with_the_expected_params)
{
   AllegroFlare::StoryboardFactory storyboard_factory(&get_font_bin_ref());
   AllegroFlare::Elements::StoryboardPages::AdvancingText* created_page =
      storyboard_factory.create_advancing_text_page("Hello Factory!");

   EXPECT_EQ(&get_font_bin_ref(), created_page->get_font_bin());
   EXPECT_EQ("Hello Factory!", created_page->get_text());
}


