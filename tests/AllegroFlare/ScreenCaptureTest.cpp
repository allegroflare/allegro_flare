
#include <gtest/gtest.h>

#include <AllegroFlare/ScreenCapture.hpp>


#include <AllegroFlare/Testing/TestNameInference.hpp>
#include <string>


TEST(AllegroFlare_ScreenCaptureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ScreenCapture screen_capture;
}


TEST(AllegroFlare_ScreenCaptureTest, create_capture__will_create_a_capture_of_the_screen)
{
   //std::string full_file_save_location = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();

   //al_init();
   //ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   //ALLEGRO_BITMAP *created_capture = AllegroFlare::ScreenCapture.capture();
   //al_save_bitmap(created_capture);
   //al_destroy_bitmap(created_capture);
}


