
#include <gtest/gtest.h>

#include <Tileo/TileAtlasBuilder.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <Tileo/Atlas.hpp>

#define TEMP_TEST_FILE_PATH "/Users/markoates/Repos/tileo/tmp/tests/"
#define TEST_TILE_ATLAS_BITMAP_PATH "/Users/markoates/Repos/tileo/tests/fixtures/tiles_dungeon_v1.1.png"


std::string build_test_filename_png(std::string test_name)
{
   return TEMP_TEST_FILE_PATH + test_name + ".png";
}


TEST(Tileo_TileAtlasBuilderTest, can_be_created_without_blowing_up)
{
   TileAtlasBuilder tile_atlast_builder;
}


TEST(Tileo_TileAtlasBuilderTest, build_extruded__will_create_an_atlas_with_tile_edges_extruded)
{
   al_init();
   al_init_image_addon();

   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   ASSERT_NE(nullptr, source_bitmap);

   Tileo::Atlas atlas;
   atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   std::vector<Tileo::TileIndexInfo> tile_index = atlas.get_tile_index();
   TileAtlasBuilder tile_atlas_builder(16, 16, tile_index);
   ALLEGRO_BITMAP *result = tile_atlas_builder.build_extruded();
   al_save_bitmap(build_test_filename_png("buid__will_create_an_atlas").c_str(), result);

   al_destroy_bitmap(result);
   //atlas.clear();
   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}



TEST(Tileo_TileAtlasBuilderTest,
   build_scaled_and_extruded__will_create_a_pixel_perfect_scaled_atlas_with_tile_edges_extruded)
{
   // TODO
}



