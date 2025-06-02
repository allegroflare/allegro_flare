
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>


#define NEUTRAL_CLEAR_COLOR ALLEGRO_COLOR{0.44, 0.5, 0.56, 1.0}


class AllegroFlare_Elements_DialogBoxFrameTestWithRenderingSetup : public ::testing::Test
{
private:
   ALLEGRO_DISPLAY *display;

public:
   void SetUp() override
   {
      al_init();
      al_init_primitives_addon();
      display = al_create_display(1920, 1080);
      clear();
   }

   void TearDown() override
   {
      al_flip_display();
      al_rest(1.0);
      al_destroy_display(display);
      al_uninstall_system();
   }

   void clear()
   {
      al_clear_to_color(NEUTRAL_CLEAR_COLOR);
      al_clear_depth_buffer(1);
   }
};



TEST(AllegroFlare_Elements_DialogBoxFrameTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;
}


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__when_allegro_is_not_installed__raises_an_exception)
{
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;
   EXPECT_THROW_GUARD_ERROR(
      dialog_box_renderer.render(),
      "AllegroFlare::Elements::DialogBoxFrame::render",
      "al_is_system_installed()"
   );
}


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__when_allegro_primitives_are_not_installed__raises_an_exception)
{
   al_init();

   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;
   EXPECT_THROW_GUARD_ERROR(
      dialog_box_renderer.render(),
      "AllegroFlare::Elements::DialogBoxFrame::render",
      "al_is_primitives_addon_initialized()"
   );

   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__when_there_is_no_allegro_display__raises_an_exception)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;

   EXPECT_THROW_GUARD_ERROR(
      dialog_box_renderer.render(),
      "AllegroFlare::Elements::DialogBoxFrame::render",
      "al_get_current_display()"
   );

   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxFrameTestWithRenderingSetup, render__draws_the_dialog_box)
{
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;
   dialog_box_renderer.render();
}


TEST_F(AllegroFlare_Elements_DialogBoxFrameTestWithRenderingSetup,
   render__with_a_partial_opacity__will_render_as_expected)
{
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;
   dialog_box_renderer.set_opacity(0.5);
   dialog_box_renderer.render();
}


