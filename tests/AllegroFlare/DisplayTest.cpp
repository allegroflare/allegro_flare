
#include <gtest/gtest.h>

#include <AllegroFlare/Display.hpp>


TEST(AllegroFlare_DisplayTest, DISABLED__can_be_created_without_blowing_up)
{
   // TODO: Rework AllegroFlare/Display and prevent this test from failing. This will require a
   // general overhaul of pieces that use Display, which expect to create the display on instanciation.
   AllegroFlare::Display display;
}


TEST(AllegroFlare_DisplayTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Display display;
}


TEST(AllegroFlare_DisplayTest, initialize__will_not_blow_up)
{
   al_init();
   AllegroFlare::Display display;
   display.initialize();
   display.destroy();
   al_uninstall_system();
}


TEST(AllegroFlare_DisplayTest, samples__will_set_the_samples)
{
   al_init();
   int samples = 4;
   AllegroFlare::Display display(1920, 1080, ALLEGRO_OPENGL, samples, 32);
   display.initialize();

   int expected_samples = samples;
   int actual_samples = al_get_display_option(display.al_display, ALLEGRO_SAMPLES);

   EXPECT_EQ(expected_samples, actual_samples);

   display.destroy();
   al_uninstall_system();
}


TEST(AllegroFlare_DisplayTest, samples__when_set_to_zero__will_work_as_expecteed)
{
   al_init();
   int samples = 0;
   AllegroFlare::Display display(1920, 1080, ALLEGRO_OPENGL, samples, 32);
   display.initialize();

   int expected_samples = samples;
   int actual_samples = al_get_display_option(display.al_display, ALLEGRO_SAMPLES);

   EXPECT_EQ(expected_samples, actual_samples);

   display.destroy();
   al_uninstall_system();
}


TEST(AllegroFlare_DisplayTest, DISBLED__fullscreen__after_initialization__will_throw_an_error)
{
   // TODO
}


TEST(AllegroFlare_DisplayTest, fullscreen__when_set_to_true__will_create_the_window_as_a_fullscreen_window)
{
   al_init();
   AllegroFlare::Display display;
   display.set_fullscreen(true);
   display.initialize();

   ASSERT_NE(nullptr, display.al_display);
   bool expected_fullscreen = true;
   bool actual_fullscreen = al_get_display_flags(display.al_display) & ALLEGRO_FULLSCREEN_WINDOW;

   EXPECT_EQ(expected_fullscreen, actual_fullscreen);

   display.destroy();
   al_uninstall_system();
}


TEST(AllegroFlare_DisplayTest, fullscreen__when_set_to_false__will_create_the_window_as_a_fullscreen_window)
{
   al_init();
   AllegroFlare::Display display;
   display.set_fullscreen(false);
   display.initialize();

   ASSERT_NE(nullptr, display.al_display);
   bool expected_fullscreen = false;
   bool actual_fullscreen = al_get_display_flags(display.al_display) & ALLEGRO_FULLSCREEN_WINDOW;

   EXPECT_EQ(expected_fullscreen, actual_fullscreen);

   display.destroy();
   al_uninstall_system();
}


TEST(AllegroFlare_DisplayTest, result_fullscreen__will_return_the_fullscreen_status_that_happened_on_creation)
{
   al_init();
   AllegroFlare::Display display;
   display.set_fullscreen(true);
   display.initialize();

   bool expected_result_fullscreen = true;
   EXPECT_EQ(expected_result_fullscreen, display.get_result_fullscreen());

   display.destroy();
   al_uninstall_system();
}


