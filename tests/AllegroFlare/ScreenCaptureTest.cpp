
#include <gtest/gtest.h>

#include <AllegroFlare/ScreenCapture.hpp>


#include <AllegroFlare/Testing/TestNameInference.hpp>
#include <allegro5/allegro_image.h>


TEST(AllegroFlare_ScreenCaptureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ScreenCapture screen_capture;
}


TEST(AllegroFlare_ScreenCaptureTest, create_capture__will_create_a_capture_of_the_screen)
{
   std::string full_file_save_location = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();

   al_init();
   al_init_image_addon(); // for al_save_bitmap

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_BITMAP *created_capture = AllegroFlare::ScreenCapture::create_capture();
   al_init_image_addon();
   al_save_bitmap(full_file_save_location.c_str(), created_capture);

   al_destroy_bitmap(created_capture);
   al_destroy_display(display);
   al_shutdown_image_addon(); // for al_save_bitmap
}


