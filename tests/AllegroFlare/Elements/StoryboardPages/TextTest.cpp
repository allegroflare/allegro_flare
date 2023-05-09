
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StoryboardPages_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   EXPECT_EQ("Text", text.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   std::string expected_error_message =
      "Text::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text(&get_font_bin_ref());
   text.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_show_the_text)
{
   std::string text_to_show = "Hello StoryboardPages/Text!";
   AllegroFlare::Elements::StoryboardPages::Text text(&get_font_bin_ref(), text_to_show);
   text.render();
   al_flip_display();
   SUCCEED();
}


