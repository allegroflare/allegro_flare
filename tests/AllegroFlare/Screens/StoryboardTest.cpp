
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_StoryboardTest : public ::testing::Test
{};

class AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/Storyboard.hpp>


TEST_F(AllegroFlare_Screens_StoryboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Storyboard storyboard;
}


TEST_F(AllegroFlare_Screens_StoryboardTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::Storyboard storyboard;
   std::string expected_error_message =
      "Storyboard::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(storyboard.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref());
   storyboard.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   render__will_draw_the_current_page_text_to_the_screen)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref(), nullptr, pages);

   storyboard.render();
   al_flip_display();

   sleep_for(2);

   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   key_down_func__will_advance_to_the_next_page)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   key_down_func__when_at_the_final_page__will_emit_a_screen_switch_event_with_the_expected_param)
{
   // TODO
}


