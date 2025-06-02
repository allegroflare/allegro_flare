
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>


#define NEUTRAL_CLEAR_COLOR ALLEGRO_COLOR{0.44, 0.5, 0.56, 1.0}


class AllegroFlare_Elements_DialogBoxFrameTestWithRenderingSetup : public ::testing::Test
{
private:
   ALLEGRO_DISPLAY *display;
   AllegroFlare::Placement2D subject_placement;

public:
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;

   void SetUp() override
   {
      al_init();
      al_init_primitives_addon();
      display = al_create_display(1920, 1080);
      al_clear_to_color(NEUTRAL_CLEAR_COLOR);
      al_clear_depth_buffer(1);
   }

   void TearDown() override
   {
      al_flip_display();
      al_rest(1.0);
      al_destroy_display(display);
      al_uninstall_system();
   }

   void render_subject()
   {
      AllegroFlare::Placement2D subject_placement;
      subject_placement.size = { dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
      subject_placement.position = { 1920/2, 1080/2 };
      subject_placement.start_transform();

      dialog_box_renderer.render();

      subject_placement.restore_transform();
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
   render_subject();
}


TEST_F(AllegroFlare_Elements_DialogBoxFrameTestWithRenderingSetup,
   render__with_a_partial_opacity__will_render_as_expected)
{
   dialog_box_renderer.set_opacity(0.5);
   render_subject();
}


