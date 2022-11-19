
#include <gtest/gtest.h>

#include <AllegroFlare/ScreenCapture.hpp>


#include <AllegroFlare/Testing/TestNameInference.hpp>
#include <AllegroFlare/Testing/Rulers.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>


TEST(AllegroFlare_ScreenCaptureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ScreenCapture screen_capture;
}


TEST(AllegroFlare_ScreenCaptureTest, create_capture__will_create_a_capture_of_the_screen)
{
   std::string full_file_save_location = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();

   al_init();
   al_init_image_addon(); // for al_save_bitmap
   al_init_primitives_addon(); // for Testing::Rulers

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   // draw some test rendering
   AllegroFlare::Testing::Rulers::draw_2d_grid(1920/2, 1080/2, 8.0f);
   al_flip_display();

   ALLEGRO_BITMAP *created_capture = AllegroFlare::ScreenCapture::create_capture();
   al_save_bitmap(full_file_save_location.c_str(), created_capture);

   al_destroy_bitmap(created_capture);
   al_destroy_display(display);
   al_shutdown_primitives_addon(); // for Testing::Rulers
   al_shutdown_image_addon(); // for al_save_bitmap
   al_uninstall_system();
}


TEST(AllegroFlare_ScreenCaptureTest, create_capture_as_scaled_bitmap__will_create_a_scaled_capture_of_the_screen)
{
   std::string full_file_save_location = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();

   al_init();
   al_init_image_addon(); // for al_save_bitmap
   al_init_primitives_addon(); // for Testing::Rulers

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   // draw some test rendering
   AllegroFlare::Testing::Rulers::draw_2d_grid(1920/2, 1080/2, 8.0f);
   al_flip_display();

   ALLEGRO_BITMAP *created_capture = AllegroFlare::ScreenCapture::create_capture_as_scaled_bitmap(192, 108);
   ASSERT_NE(nullptr, created_capture);
   ASSERT_EQ(192, al_get_bitmap_width(created_capture));
   ASSERT_EQ(108, al_get_bitmap_height(created_capture));

   al_save_bitmap(full_file_save_location.c_str(), created_capture);

   al_destroy_bitmap(created_capture);
   al_destroy_display(display);
   al_shutdown_primitives_addon(); // for Testing::Rulers
   al_shutdown_image_addon(); // for al_save_bitmap
   al_uninstall_system();
}


// TODO: add tests for helper functions


