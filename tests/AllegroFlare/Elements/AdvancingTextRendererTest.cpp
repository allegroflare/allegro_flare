
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
   EXPECT_THROW_GUARD_ERROR(
      advancing_text_renderer.render(),
      "AllegroFlare::Elements::AdvancingTextRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref());
   advancing_text_renderer.render();
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__with_text__will_draw_the_text_as_expected)
{
   std::string text = "Hello AdvancingTextRenderer!";
   AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(&get_font_bin_ref(), text);
   advancing_text_renderer.render();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_AdvancingTextRendererTestWithAllegroRenderingFixture,
   CAPTURE__VISUAL__render__with_text_and_num_revealed_characters__will_draw_the_number_of_revealed_characters_from_the\
text)
{
   std::string text = "Hello AdvancingTextRenderer!";

   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      clear();
      int characters_to_reveal = i / 2;
      AllegroFlare::Elements::AdvancingTextRenderer advancing_text_renderer(
         &get_font_bin_ref(),
         text,
         characters_to_reveal
      );
      advancing_text_renderer.render();
      al_flip_display();
   }
}


