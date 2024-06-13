#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/WorldMapRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_WorldMapRendererTest : public ::testing::Test {};
class AllegroFlare_WorldMapRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_WorldMapRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMapRenderer world_map_renderer;
}


TEST_F(AllegroFlare_WorldMapRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::WorldMapRenderer world_map_renderer;
   EXPECT_THROW_GUARD_ERROR(
      world_map_renderer.render(),
      "AllegroFlare::WorldMapRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_WorldMapRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::WorldMapRenderer world_map_renderer;
   EXPECT_THROW_GUARD_ERROR(
      world_map_renderer.render(),
      "AllegroFlare::WorldMapRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::WorldMapRenderer world_map_renderer;
   EXPECT_THROW_GUARD_ERROR(
      world_map_renderer.render(),
      "AllegroFlare::WorldMapRenderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_WorldMapRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::WorldMapRenderer world_map_renderer;
   EXPECT_THROW_GUARD_ERROR(
      world_map_renderer.render(),
      "AllegroFlare::WorldMapRenderer::render",
      "font_bin"
   );
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_WorldMapRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::WorldMapRenderer world_map_renderer(&get_font_bin_ref());
   world_map_renderer.render();
   al_flip_display();
   sleep_for(1);
}


