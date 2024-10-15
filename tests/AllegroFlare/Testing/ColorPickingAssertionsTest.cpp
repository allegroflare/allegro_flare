
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ColorPickingAssertions.hpp>


TEST(AllegroFlare_Testing_ColorPickingAssertions, EXPECT_PICKED_COLOR_EQ__will_succeed_when_the_bitmap_has_a_\
pixel_at_that_coordinate)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.6f, 0.2f, 0.8f, 1.0f};
   al_clear_to_color(color);

   ALLEGRO_COLOR expected_color = color;
   ALLEGRO_BITMAP *subject_surface = al_get_backbuffer(al_get_current_display());

   EXPECT_PICKED_COLOR_EQ(expected_color, subject_surface, 400, 300);

   al_destroy_display(display);
   al_uninstall_system();
}


// TODO: Add test for "will fail when color does not match"

// TODO: Add tests for ASSERT_* variants


