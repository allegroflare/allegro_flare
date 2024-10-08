

// NOTE: This class has been repositioned many times, was once a class contained in the PrimMeshAtlas class. Its role
// is unclear at the last time of refactoring. What I'm trying to say is the class and tests could use some cleanup.

// TODO: Clean up this class, the correctness of the tests and their tested components, and their naming

// TODO: Consider if this class is needed or even used


#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>



// TODO: Consider removing this method for a cleaner alternative
static std::string build_test_filename_png(std::string test_name)
{
   return "tmp/test_snapshots/" + test_name + ".png";
}


TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::TileAtlasBuilder tile_atlast_builder;
}


TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest, build_extruded__will_create_an_atlas_with_tile_edges_extruded)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);
   std::string data_path = deployment_environment.get_data_folder_path();
   std::string test_tile_atlas_filename = "tiles_dungeon_v1.1.png";

   al_init();
   al_init_image_addon();

   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap((data_path + test_tile_atlas_filename).c_str());
   ASSERT_NE(nullptr, source_bitmap);

   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = atlas.get_tile_index();
   AllegroFlare::TileMaps::TileAtlasBuilder tile_atlas_builder(16, 16, tile_index);
   ALLEGRO_BITMAP *result = tile_atlas_builder.build_extruded();
   al_save_bitmap(build_test_filename_png("build__will_create_an_atlas").c_str(), result);

   al_destroy_bitmap(result);
   //atlas.clear();
   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}



TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   build_extruded__will_work_on_atlases_where_source_images_are_tall_or_wide_and_not_perfect_square_dimensions)
{
   // TODO
}



TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   build_scaled_and_extruded__will_create_a_pixel_perfect_scaled_atlas_with_tile_edges_extruded)
{
   // TODO
}



/*
// TODO: Consider if this test needs to be located somewhere else
TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   get_tile_sub_bitmap__returns_the_sub_bitmap_of_the_tile)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);
   std::string data_path = deployment_environment.get_data_folder_path();
   std::string test_tile_atlas_filename = "tiles_dungeon_v1.1.png";

   al_init();
   al_init_image_addon();
   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap((data_path + test_tile_atlas_filename).c_str());
   //ALLEGRO_BITMAP* source_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   ASSERT_NE(nullptr, source_bitmap);

   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> actual_tile_index = atlas.get_tile_index();
   ALLEGRO_BITMAP *expected_sub_bitmap = actual_tile_index[32].get_sub_bitmap();
   ASSERT_NE(nullptr, expected_sub_bitmap);
   EXPECT_EQ(atlas.get_tile_sub_bitmap(32), actual_tile_index[32].get_sub_bitmap());

   //atlas.clear();
   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}
*/


TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   get_tile_sub_bitmap__when_a_tile_does_not_exist_at_that_index__returns_a_nullptr)
{
   // TODO
}




