
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
   render__will_draw_the_current_page_text_to_the_screen)
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
   update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

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


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   current_page_num__is_initialized_with_a_value_of_zero)
{
   AllegroFlare::Elements::Storyboard storyboard;
   EXPECT_EQ(0, storyboard.get_current_page_num());
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__will_advance_to_the_next_page_and_return_true)
{
   std::vector<std::string> pages = {
      "This is page 1.",
      "The second page looks like this.",
      "A final page is this one, indeed.",
   };
   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.render();
   al_flip_display();

   EXPECT_EQ(0, storyboard.get_current_page_num()); // TODO: this line should be a separate test
   for (int i=0; i<(pages.size()-1); i++)
   {
      EXPECT_EQ(true, storyboard.advance_page());
      int expected_page_num = i+1;
      EXPECT_EQ(expected_page_num, storyboard.get_current_page_num());
   }

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance_page__when_at_the_final_page__will_return_false)
{
   std::vector<std::string> pages = { "This is page 1.", "Here is the last page." };

   AllegroFlare::Elements::Storyboard storyboard(&get_font_bin_ref(), pages);

   storyboard.advance_page();

   // now at the last page
   EXPECT_EQ(false, storyboard.advance_page());
}


