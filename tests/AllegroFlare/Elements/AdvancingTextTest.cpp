
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_AdvancingTextTest : public ::testing::Test
{};

class AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/AdvancingText.hpp>


TEST_F(AllegroFlare_Elements_AdvancingTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::AdvancingText advancing_text;
}


TEST_F(AllegroFlare_Elements_AdvancingTextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::AdvancingText advancing_text;
   std::string expected_error_message =
      "AdvancingText::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(advancing_text.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref());
   advancing_text.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.all_characters_are_revealed());
   advancing_text.start();
   EXPECT_EQ(false, advancing_text.all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_finished_to_false)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.jump_to_end();
   EXPECT_EQ(true, advancing_text.get_finished());
   advancing_text.start();
   EXPECT_EQ(false, advancing_text.get_finished());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.start();
   advancing_text.reveal_all_characters();
   EXPECT_EQ(false, advancing_text.get_finished());
   advancing_text.update();
   EXPECT_EQ(true, advancing_text.get_finished());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   EXPECT_EQ(false, advancing_text.all_characters_are_revealed());
   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_set_the_page_to_finished)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.start();
   advancing_text.reveal_all_characters();
   EXPECT_EQ(false, advancing_text.get_finished());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   jump_to_end__when_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.start();
   advancing_text.reveal_all_characters();
   EXPECT_EQ(false, advancing_text.get_finished());
   advancing_text.jump_to_end();
   EXPECT_EQ(true, advancing_text.get_finished());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   jump_to_end__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.start();
   advancing_text.jump_to_end();
   EXPECT_EQ(true, advancing_text.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   jump_to_end__when_not_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.start();
   advancing_text.jump_to_end();
   EXPECT_EQ(true, advancing_text.get_finished());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   DISABLED__VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.reveal_all_characters();
   advancing_text.render();
   al_flip_display();

   sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   DISABLED__VISUAL__render__will_respect__width)
{
   std::string text = "Hello AdvancingText!  This text should fit to the width of 800 pixels.";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   advancing_text.set_width(1000);

   advancing_text.reveal_all_characters();
   advancing_text.render();
   al_flip_display();

   sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   DISABLED__VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(&get_font_bin_ref(), text);

   for (int i=0; i<18; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      advancing_text.update();

      advancing_text.render();
      al_flip_display();

      sleep_for_frame();
   }

   SUCCEED();
}


