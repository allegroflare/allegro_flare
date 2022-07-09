
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_StoryboardTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Storyboard.hpp>


TEST_F(AllegroFlare_Elements_StoryboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Storyboard storyboard;
}


TEST_F(AllegroFlare_Elements_StoryboardTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Storyboard storyboard;
   std::string expected_error_message =
      "Storyboard::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref());
   storyboard.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   current_page_num__is_initialized_with_a_value_of_zero)
{
   AllegroFlare::Elements::Storyboard storyboard;
   EXPECT_EQ(0, storyboard.get_current_page_num());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.reveal_all_characters();
   storyboard.render();
   al_flip_display();

   //sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   for (int i=0; i<18; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      storyboard.update();

      storyboard.render();
      al_flip_display();

      //sleep_for_frame();
   }

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__render__when_able_to_advance_to_the_next_page__will_draw_the_cursor_animated)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   for (int i=0; i<12; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      storyboard.render();
      al_flip_display();
      sleep_for_frame();
   }

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   update__after_revealing_the_last_character__will_enable_advancing_to_the_next_page)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one.", "Page two." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_can_advance_to_next());
   storyboard.update();
   EXPECT_EQ(true, storyboard.get_can_advance_to_next());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(false, storyboard.all_characters_are_revealed());
   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_allow_advancing_to_the_next_page)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_can_advance_to_next());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__will_allow_advancing_to_the_next_page__even_if_all_characters_have_not_been_revealed)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one.", "Second page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   EXPECT_EQ(true, storyboard.advance_page());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__will_set__can_advance_start_at__to_the_current_time)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one.", "Second page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(0, storyboard.get_can_advance_started_at());
   storyboard.permit_advancing_page();
   EXPECT_NE(0, storyboard.get_can_advance_started_at());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__when_already_permitted__will_not_modify__can_advance_start_at)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one.", "Second page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   float latest_can_advance_started_at = storyboard.get_can_advance_started_at();
   sleep_for(0.1); // to enable possible failing condition
   storyboard.permit_advancing_page();
   EXPECT_EQ(latest_can_advance_started_at, storyboard.get_can_advance_started_at());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__will_not_modify_the_number_of_revealed_characters)
{
   std::vector<std::string> pages = { "This are characters that need to be revealed one-by-one.", "Second page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   EXPECT_EQ(0, storyboard.get_revealed_characters_count());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__when_at_the_final_page__will_return_false)
{
   std::vector<std::string> pages = { "This is the final page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(true, storyboard.permit_advancing_page());
   storyboard.advance_page();
   EXPECT_EQ(false, storyboard.permit_advancing_page());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__when_not_allowed_to_advance_to_the_next_page__will_return_false_and_not_advance_to_the_next_page)
{
   std::vector<std::string> pages = { "This is the storyboard page text." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(false, storyboard.advance_page());
   EXPECT_EQ(0, storyboard.get_current_page_num());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__will_advance_to_the_next_page_and_return_true)
{
   std::vector<std::string> pages = { "This is page 1.", "The second page looks like this." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   EXPECT_EQ(true, storyboard.advance_page());
   EXPECT_EQ(1, storyboard.get_current_page_num());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__will_reset_the_revealed_characters_count_to_zero)
{
   std::vector<std::string> pages = { "This is page 1.", "The second page looks like this." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.reveal_all_characters();
   storyboard.permit_advancing_page();
   ASSERT_NE(0, storyboard.get_revealed_characters_count());
   storyboard.advance_page();
   EXPECT_EQ(0, storyboard.get_revealed_characters_count());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__will_unpermit_advancing_to_subsequent_pages)
{
   std::vector<std::string> pages = { "This is page 1.", "The second page looks like this." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   storyboard.advance_page();
   EXPECT_EQ(false, storyboard.get_can_advance_to_next());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__when_at_the_final_page__will_return_false)
{
   std::vector<std::string> pages = { "This is page 1.", "Here is the last page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.advance_page();
   EXPECT_EQ(false, storyboard.advance_page());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__when_at_the_final_page__will_return_false_even_if_permit_advancing_page_has_been_called)
{
   std::vector<std::string> pages = { "In this test, there is only one page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   EXPECT_EQ(false, storyboard.advance_page());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters_and_return_true)
{
   std::vector<std::string> pages = { "In this test, there is only one page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(true, storyboard.advance());
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_permit_advancing_to_the_next_page)
{
   std::vector<std::string> pages = { "In this test, there is only one page." };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   EXPECT_EQ(true, storyboard.advance());
   EXPECT_EQ(true, storyboard.get_can_advance_to_next());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__when_advancing_to_the_next_page_is_permitted__will_advance_to_the_next_page_and_return_true)
{
   std::vector<std::string> pages = { "This is page 1.", "This is the second page" };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.permit_advancing_page();
   EXPECT_EQ(true, storyboard.advance());
   EXPECT_EQ(1, storyboard.get_current_page_num());
}


