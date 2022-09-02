
#include <gtest/gtest.h>

#include <AllegroFlare/ImageGenerator.hpp>


TEST(AllegroFlare_ImageGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ImageGenerator image_generator;
}


TEST(AllegroFlare_ImageGeneratorTest, create_pattern_x__will_create_a_bitmap_with_the_pattern)
{
   al_init();

   AllegroFlare::ImageGenerator image_generator;
   ALLEGRO_BITMAP *bitmap = image_generator.create_pattern_x();

   ASSERT_NE(nullptr, bitmap);
   ASSERT_EQ(256, al_get_bitmap_width(bitmap));
   ASSERT_EQ(256, al_get_bitmap_height(bitmap));

   al_uninstall_system();
}


