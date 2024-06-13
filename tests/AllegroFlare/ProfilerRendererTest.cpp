#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


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
   EXPECT_THROW_GUARD_ERROR(
      profiler_renderer.render(),
      "AllegroFlare::ProfilerRenderer::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   EXPECT_THROW_GUARD_ERROR(
      profiler_renderer.render(),
      "AllegroFlare::ProfilerRenderer::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   EXPECT_THROW_GUARD_ERROR(
      profiler_renderer.render(),
      "AllegroFlare::ProfilerRenderer::render",
      "al_is_font_addon_initialized()"
   );
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_ProfilerRendererTest, render__without_a_font_bin__raises_an_error)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   AllegroFlare::ProfilerRenderer profiler_renderer;
   EXPECT_THROW_GUARD_ERROR(
      profiler_renderer.render(),
      "AllegroFlare::ProfilerRenderer::render",
      "font_bin"
   );
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


