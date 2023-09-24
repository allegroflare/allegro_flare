
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_AdvancingTextRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/AdvancingTextRenderer.hpp>


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer;
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer;
   std::string expected_error_message =
      "AdvancingTextRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(advancing_text_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref());
   advancing_text_renderer.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   advancing_text_renderer.reveal_all_characters();
   EXPECT_EQ(true, advancing_text_renderer.get_all_characters_are_revealed());
   advancing_text_renderer.start();
   EXPECT_EQ(false, advancing_text_renderer.get_all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   start__will_set_all_characters_to_revealed_to_false)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   advancing_text_renderer.reveal_all_characters();
   EXPECT_EQ(true, advancing_text_renderer.get_all_characters_are_revealed());
   advancing_text_renderer.start();
   EXPECT_EQ(false, advancing_text_renderer.get_all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   after_all_characters_have_been_revealed__will_set_all_characters_are_revealed_to_true)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   advancing_text_renderer.start();
   advancing_text_renderer.reveal_all_characters();
   EXPECT_EQ(true, advancing_text_renderer.get_all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   EXPECT_EQ(false, advancing_text_renderer.get_all_characters_are_revealed());
   advancing_text_renderer.reveal_all_characters();
   EXPECT_EQ(true, advancing_text_renderer.get_all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   advancing_text_renderer.reveal_all_characters();
   advancing_text_renderer.render();
   al_flip_display();

   sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   VISUAL__render__will_respect__width)
{
   std::string text = "Hello AdvancingTextRenderer!  This text should fit to the width of 800 pixels.";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   advancing_text_renderer.set_width(1000);

   advancing_text_renderer.reveal_all_characters();
   advancing_text_renderer.render();
   al_flip_display();

   sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   VISUAL__update__will_reveal_the_characters_in_the_page_one_by_one)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);

   for (int i=0; i<18; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      advancing_text_renderer.update();

      advancing_text_renderer.render();
      al_flip_display();

      sleep_for_frame();
   }

   SUCCEED();
}


