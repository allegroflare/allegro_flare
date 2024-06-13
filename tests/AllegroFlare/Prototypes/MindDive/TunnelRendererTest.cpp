#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Prototypes_MindDive_TunnelRendererTest : public ::testing::Test {};
class AllegroFlare_Prototypes_MindDive_TunnelRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/MindDive/TunnelRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
   EXPECT_THROW_GUARD_ERROR(
      tunnel_renderer.render(),
      "AllegroFlare::Prototypes::MindDive::TunnelRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
   EXPECT_THROW_GUARD_ERROR(
      tunnel_renderer.render(),
      "AllegroFlare::Prototypes::MindDive::TunnelRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
   tunnel_renderer.render();
   al_flip_display();
   sleep_for(1);
}


