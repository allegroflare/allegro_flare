
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Color.hpp>


class AllegroFlare_Elements_StopwatchTest : public ::testing::Test
{};

class AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Stopwatch.hpp>


TEST_F(AllegroFlare_Elements_StopwatchTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
}


TEST_F(AllegroFlare_Elements_StopwatchTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
   EXPECT_THROW_GUARD_ERROR(
      stopwatch.render(),
      "AllegroFlare::Elements::Stopwatch::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_StopwatchTest, render__without_font_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::Stopwatch stopwatch;
   EXPECT_THROW_GUARD_ERROR(
      stopwatch.render(),
      "AllegroFlare::Elements::Stopwatch::render",
      "al_is_font_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture, render__without_a_font_bin__will_raise_an_error)
{
   AllegroFlare::Elements::Stopwatch stopwatch;
   EXPECT_THROW_GUARD_ERROR(
      stopwatch.render(),
      "AllegroFlare::Elements::Stopwatch::render",
      "font_bin"
   );
}


TEST_F(AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture,
  CAPTURE__fit_placement_width_and_height_to_stopwatch__will_set_the_placement_width_and_height_to_fit_the_stopwatch)
{
   AllegroFlare::Timer timer;
   AllegroFlare::Elements::Stopwatch stopwatch(&get_font_bin_ref(), &timer);
   stopwatch.get_placement_ref() = build_centered_placement();
   stopwatch.fit_placement_width_and_height_to_stopwatch();

   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   stopwatch.render();
   stopwatch.get_placement_ref().draw_box(AllegroFlare::Color::MintCream);
   draw_rulers();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture,
   CAPTURE__render__will_display_the_time_on_the_timer)
{
   AllegroFlare::Timer timer;
   AllegroFlare::Elements::Stopwatch stopwatch(&get_font_bin_ref(), &timer);
   stopwatch.get_placement_ref() = build_centered_placement();
   timer.start();

   float seconds = 0.2;
   float fps = 60;
   for (int frame=0; frame<(seconds * fps); frame++)
   {
      al_clear_to_color(AllegroFlare::Color::Eigengrau);
      stopwatch.render();
      al_flip_display();
      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_StopwatchTestWithAllegroRenderingFixture,
   CAPTURE__render__will_display_the_timer_with_color_font_identifier_and_font_size_options)
{
   AllegroFlare::Timer timer;
   AllegroFlare::Elements::Stopwatch stopwatch(&get_font_bin_ref(), &timer);
   stopwatch.get_placement_ref() = build_centered_placement();
   stopwatch.set_color(AllegroFlare::Color::Aquamarine);
   stopwatch.set_font_identifier("plantin-mt-light.ttf");
   stopwatch.set_font_size(-160);

   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   stopwatch.render();
   al_flip_display();
}


