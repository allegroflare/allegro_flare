#define ALLEGRO_UNSTABLE


#include <gtest/gtest.h>

#include <AllegroFlare/ImageGenerator.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> // for saving snapshots as PNG


#define TEST_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"



TEST(AllegroFlare_ImageGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ImageGenerator image_generator;
}


TEST(AllegroFlare_ImageGeneratorTest, create_pattern_x__will_create_a_bitmap_with_the_pattern)
{
   al_init();
   al_init_primitives_addon();
   std::string SNAPSHOT_LOCATION = "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/create_pattern_x.png";

   AllegroFlare::ImageGenerator image_generator;
   ALLEGRO_BITMAP *bitmap = image_generator.create_pattern_x(512);

   ASSERT_NE(nullptr, bitmap);
   //ASSERT_EQ(256, al_get_bitmap_width(bitmap));
   //ASSERT_EQ(256, al_get_bitmap_height(bitmap));

   al_init_image_addon();
   al_save_bitmap(SNAPSHOT_LOCATION.c_str(), bitmap);
   al_shutdown_image_addon();

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


