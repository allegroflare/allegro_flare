
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>


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


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__draws_the_dialog_box)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;

   dialog_box_renderer.render();
   al_flip_display();
   std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__respects_opacity)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;

   dialog_box_renderer.set_opacity(0.5);

   al_clear_to_color(ALLEGRO_COLOR{0.05, 0.05, 0.055, 1.0});
   dialog_box_renderer.render();
   al_flip_display();
   std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST(AllegroFlare_Elements_DialogBoxFrameTest, render__when_the_dialog_box_is_finish__renders_special_empty_text)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::Elements::DialogBoxFrame dialog_box_renderer;

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


