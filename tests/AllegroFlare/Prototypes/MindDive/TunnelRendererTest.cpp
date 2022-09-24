#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


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
   std::string expected_error_message =
      "TunnelRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tunnel_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
   std::string expected_error_message =
      "TunnelRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tunnel_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelRenderer tunnel_renderer;
   tunnel_renderer.render();
   al_flip_display();
   sleep_for(1);
}


