#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_ProfilerRendererTest : public ::testing::Test {};
class AllegroFlare_ProfilerRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/ProfilerRenderer.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_ProfilerRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ProfilerRenderer profiler_renderer;
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::ProfilerRenderer profiler_renderer;
   std::string expected_error_message =
      "ProfilerRenderer::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(profiler_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   std::string expected_error_message =
      "ProfilerRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(profiler_renderer.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   std::string expected_error_message =
      "ProfilerRenderer::render: error: guard \"al_is_font_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(profiler_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   std::string expected_error_message =
      "ProfilerRenderer::render: error: guard \"font_bin\" not met";
   EXPECT_THROW_WITH_MESSAGE(profiler_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}   


TEST_F(AllegroFlare_ProfilerRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::ProfilerRenderer profiler_renderer(&get_font_bin_ref());
   std::map<std::string, AllegroFlare::Timer> timers;
   profiler_renderer.set_timers(&timers);
   profiler_renderer.render();
   al_flip_display();
   sleep_for(1);
}


