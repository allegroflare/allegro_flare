#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/CharacterFeatureRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   EXPECT_THROW_GUARD_ERROR(
      character_feature_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   EXPECT_THROW_GUARD_ERROR(
      character_feature_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   EXPECT_THROW_GUARD_ERROR(
      character_feature_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   EXPECT_THROW_GUARD_ERROR(
      character_feature_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::FontBin font_bin;
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer(&font_bin);
   EXPECT_THROW_GUARD_ERROR(
      character_feature_renderer.render(),
      "AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer::render",
      "bitmap_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer(
         &get_font_bin_ref(),
         &get_bitmap_bin_ref()
      );
   character_feature_renderer.set_character_image_identifier("mystery-cat-x1080-01.png");
   character_feature_renderer.set_character_name("Mystery Cat");
   character_feature_renderer.set_description(
      "Shrouded in a dark hood, this cat navigates the shadows while leaving critical clues to perplexing riddles"
   );
   character_feature_renderer.render();
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTestWithAllegroRenderingFixture,
   VISUAL__render__will_render_a_reveal_animation)
{
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer(
         &get_font_bin_ref(),
         &get_bitmap_bin_ref()
      );
   character_feature_renderer.set_character_image_identifier("mystery-cat-x1080-01.png");
   character_feature_renderer.set_character_name("Mystery Cat");
   character_feature_renderer.set_description(
      "Shrouded in a dark hood, this cat navigates the shadows while leaving critical clues to perplexing riddles"
   );

   float started_at = al_get_time();
   float duration = character_feature_renderer.DEFAULT_DURATION + 0.2;

   while ((al_get_time() - started_at) < duration)
   {
      float age = al_get_time() - started_at;
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      character_feature_renderer.set_age(age);
      character_feature_renderer.render();
      al_flip_display();
      sleep_for_frame();
   }
}


