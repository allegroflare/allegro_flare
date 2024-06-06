#define ALLEGRO_UNSTABLE


#include <gtest/gtest.h>

#include <AllegroFlare/ImageGenerator.hpp>
#include <AllegroFlare/Interpolators.hpp>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h> // for saving snapshots as PNG


#define TEST_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"



TEST(AllegroFlare_ImageGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ImageGenerator image_generator;
}


TEST(AllegroFlare_ImageGeneratorTest, create_pattern_x__without_primitives_addon_initialized__will_return_nullptr)
{
   // TODO
}

TEST(AllegroFlare_ImageGeneratorTest, create_pattern_x__will_create_a_bitmap_with_the_pattern)
{
   al_init();
   al_init_primitives_addon();
   std::string SNAPSHOT_LOCATION = "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/create_pattern_x.png";

   AllegroFlare::ImageGenerator image_generator;
   ALLEGRO_BITMAP *bitmap = image_generator.create_pattern_x(512);

   ASSERT_NE(nullptr, bitmap);
   EXPECT_EQ(512, al_get_bitmap_width(bitmap));
   EXPECT_EQ(512, al_get_bitmap_height(bitmap));

   al_init_image_addon();
   al_save_bitmap(SNAPSHOT_LOCATION.c_str(), bitmap);
   al_shutdown_image_addon();

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_ImageGeneratorTest, generate_interpolator_graph_bitmap__will_render_a_bitmap_of_the_interpolator)
{
   al_init();
   al_init_primitives_addon();
   std::string SNAPSHOT_LOCATION =
      "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/generate_interpolator_graph_bitmap.png";

   AllegroFlare::ImageGenerator image_generator;
   ALLEGRO_BITMAP *bitmap = image_generator.generate_interpolator_graph_bitmap(
      AllegroFlare::Interpolators::double_fast_in,
      1024,
      512
   );

   ASSERT_NE(nullptr, bitmap);
   EXPECT_EQ(1024, al_get_bitmap_width(bitmap));
   EXPECT_EQ(512, al_get_bitmap_height(bitmap));

   al_init_image_addon();
   al_save_bitmap(SNAPSHOT_LOCATION.c_str(), bitmap);
   al_shutdown_image_addon();

   al_shutdown_primitives_addon();
   al_uninstall_system();
}


