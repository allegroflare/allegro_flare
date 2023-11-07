
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/IntertitleRenderer.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/EventNames.hpp> // TODO: is this needed?


//#include <gtest/gtest.h>

//#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   //try { code; FAIL() << "Expected " # raised_exception_type; } \
   //catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   //catch (...) { FAIL() << "Expected " # raised_exception_type; }

//#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

//#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


//#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard;
}


//TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest, has_the_expected_type)
//{
   //AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer advancing_text;
   //EXPECT_EQ("IntertitleRenderer", advancing_text.get_type());
//}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard;
   std::string expected_error_message =
      "IntertitleRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref());
   storyboard.render();
   SUCCEED();
}


/*
TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
   storyboard.start();
   EXPECT_EQ(false, storyboard.all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   start__will_set_finished_to_false)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(true, storyboard.get_finished());
   storyboard.start();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_before_wait_duration_after_all_characters_are_revealed_has_\
passed__will_not_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_after_wait_duration_after_all_characters_are_revealed_has_\
passed__will_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   al_rest(3.1); // TODO: Replace this wait with injected time and a configurable wait duration
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(false, storyboard.all_characters_are_revealed());
   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_set_the_page_to_finished)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.advance();
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_not_set_finished_to_true)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(false, storyboard.get_finished());
}
*/


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   //storyboard.reveal_all_characters();
   storyboard.set_revealed_characters_count(999);
   storyboard.render();
   al_flip_display();

   //sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   int num_revealed_characters = 0;
   for (int i=0; i<32; i++)
   {
      clear();
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      num_revealed_characters++;

      storyboard.set_revealed_characters_count(num_revealed_characters);
      storyboard.render();
      al_flip_display();

      sleep_for_frame();
   }

   SUCCEED();
}



