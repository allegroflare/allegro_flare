
#include <gtest/gtest.h>

#include <AllegroFlare/BitmapInfo.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <allegro5/allegro_image.h>


TEST(AllegroFlare_BitmapInfoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::BitmapInfo bitmap_info;
}


TEST(AllegroFlare_BitmapInfoTest, build_report__will_generate_a_report_with_the_bitmap_info)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string bitmaps_path = deployment_environment.get_data_folder_path() + "bitmaps/";

   al_init();
   al_init_image_addon();

   ALLEGRO_BITMAP *bitmap = al_load_bitmap((bitmaps_path + "assistant-01.gif").c_str());
   ASSERT_NE(nullptr, bitmap);
   
   AllegroFlare::BitmapInfo bitmap_info(bitmap);
   bitmap_info.initialize();

   std::cout << bitmap_info.build_report();

   al_destroy_bitmap(bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}


