
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/IntertitleRenderer.hpp>


TEST(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer intertitle_renderer;
}


/*

#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_StoryboardPages_AdvancingTextTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::AdvancingText advancing_text;
   EXPECT_EQ("AdvancingText", advancing_text.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard;
   std::string expected_error_message =
      "AdvancingText::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref());
   storyboard.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
   storyboard.start();
   EXPECT_EQ(false, storyboard.all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_finished_to_false)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(true, storyboard.get_finished());
   storyboard.start();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_before_wait_duration_after_all_characters_are_revealed_has_\
passed__will_not_set_finished_to_true)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_after_wait_duration_after_all_characters_are_revealed_has_\
passed__will_set_finished_to_true)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   al_rest(3.1); // TODO: Replace this wait with injected time and a configurable wait duration
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(false, storyboard.all_characters_are_revealed());
   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_set_the_page_to_finished)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   advance__when_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.advance();
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_not_set_finished_to_true)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   storyboard.render();
   al_flip_display();

   //sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_AdvancingTextTestWithAllegroRenderingFixture,
   DISABLED__VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::string text = "Hello StoryboardPages::AdvancingText!";
   AllegroFlare::Elements::StoryboardPages::AdvancingText storyboard(&get_font_bin_ref(), text);

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



*/
