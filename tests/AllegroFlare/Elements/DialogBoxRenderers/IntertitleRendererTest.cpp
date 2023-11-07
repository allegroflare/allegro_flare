
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/IntertitleRenderer.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/EventNames.hpp> // TODO: is this needed?


class AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest : public ::testing::Test
{};

class AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleRendererTest,
   render__without_allegro_initialized__raises_an_error)
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


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__will_draw_the_current_page_text_to_the_screen)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.set_revealed_characters_count(999);
   storyboard.render();
   al_flip_display();

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
      num_revealed_characters++;

      storyboard.set_revealed_characters_count(num_revealed_characters);
      storyboard.render();
      al_flip_display();

      sleep_for_frame();
   }

   SUCCEED();
}



