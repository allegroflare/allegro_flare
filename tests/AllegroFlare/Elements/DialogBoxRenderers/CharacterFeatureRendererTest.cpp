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
   std::string expected_error_message =
      "CharacterFeatureRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(character_feature_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   std::string expected_error_message =
      "CharacterFeatureRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(character_feature_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_CharacterFeatureRendererTest,
   render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogBoxRenderers::CharacterFeatureRenderer character_feature_renderer;
   std::string expected_error_message =
      "CharacterFeatureRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(character_feature_renderer.render(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "CharacterFeatureRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(character_feature_renderer.render(), std::runtime_error, expected_error_message);
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
   std::string expected_error_message =
      "CharacterFeatureRenderer::render: error: guard \"bitmap_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(character_feature_renderer.render(), std::runtime_error, expected_error_message);
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
   character_feature_renderer.render();
   al_flip_display();
   sleep_for(1);
}


