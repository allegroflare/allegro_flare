
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText.hpp>


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText advancing_text;
   EXPECT_EQ("AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText", advancing_text.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard;
   std::string expected_error_message =
      "ImageWithAdvancingText::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref());
   storyboard.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
   storyboard.start();
   EXPECT_EQ(false, storyboard.all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_finished_to_false)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(true, storyboard.get_finished());
   storyboard.start();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.update();
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(false, storyboard.all_characters_are_revealed());
   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_set_the_page_to_finished)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   advance__when_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.advance();
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_not_set_finished_to_true)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   storyboard.render();
   al_flip_display();

   //sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ImageWithAdvancingTextTestWithAllegroRenderingFixture,
   DISABLED__VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::string text = "Hello StoryboardPages::ImageWithAdvancingText!";
   AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText storyboard(&get_font_bin_ref(), text);

   for (int i=0; i<18; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      storyboard.update();

      storyboard.render();
      al_flip_display();

      sleep_for_frame();
   }

   SUCCEED();
}


