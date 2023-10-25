#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Elements/DialogBoxRenderers/ChapterTitleRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer;
   std::string expected_error_message =
      "ChapterTitleRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(chapter_title_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest,
   render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer;
   std::string expected_error_message =
      "ChapterTitleRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(chapter_title_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest,
   render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer;
   std::string expected_error_message =
      "ChapterTitleRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(chapter_title_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTest,
   render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer;
   std::string expected_error_message =
      "ChapterTitleRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(chapter_title_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer(&get_font_bin_ref());
   chapter_title_renderer.set_age(chapter_title_renderer.get_duration()/2);
   chapter_title_renderer.render();
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_ChapterTitleRendererTestWithAllegroRenderingFixture,
   VISUAL__render__will_show_a_show_and_hide_animation)
{
   AllegroFlare::Elements::DialogBoxRenderers::ChapterTitleRenderer chapter_title_renderer(&get_font_bin_ref());
   chapter_title_renderer.set_title_text("Chapter 4: Why I Write Such Good Titles");
   float started_at = al_get_time();
   float duration = 6.0f;

   while ((al_get_time() - started_at) < duration)
   {
      float age = al_get_time() - started_at;
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      chapter_title_renderer.set_age(age);
      chapter_title_renderer.render();
      al_flip_display();
      sleep_for_frame();
   }
}


