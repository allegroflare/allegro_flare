
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


TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest, create_extruded__will_create_an_atlas_with_tile_edges_extruded)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);
   std::string data_path = deployment_environment.get_data_folder_path();
   std::string test_tile_atlas_filename = "tiles_dungeon_v1.1.png";

   al_init();
   al_init_image_addon();

   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap((data_path + test_tile_atlas_filename).c_str());
   ASSERT_NE(nullptr, source_bitmap);

   AllegroFlare::TileMaps::PrimMeshAtlas dummy_atlas;
   dummy_atlas.duplicate_bitmap_and_load(source_bitmap, 16, 16, 0);

   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = dummy_atlas.get_tile_index();
   //AllegroFlare::TileMaps::TileAtlasBuilder tile_atlas_builder(16, 16, tile_index);
   //ALLEGRO_BITMAP *result = tile_atlas_builder.create_extruded();
   ALLEGRO_BITMAP *result = AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded(&tile_index);

   // TODO: Pick pixel tests
   al_save_bitmap(build_test_filename_png("build__will_create_an_atlas").c_str(), result);

   // dummy_atlas.destroy(); TOOD: Call this destroy
                          // TODO: Call destroy in other tests and ensure it's called in other locations

   al_destroy_bitmap(result);
   //atlas.clear();
   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   create_extruded__will_correctly_create_an_atlas_with_tile_edges_extruded_when_dimensions_are_not_16x16)
{
   AllegroFlare::DeploymentEnvironment deployment_environment(AllegroFlare::DeploymentEnvironment::ENVIRONMENT_TEST);
   std::string data_path = deployment_environment.get_data_folder_path();
   std::string test_tile_atlas_filename = "bitmaps/ascii_like-02.png";

   al_init();
   al_init_image_addon();

   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap((data_path + test_tile_atlas_filename).c_str());
   ASSERT_NE(nullptr, source_bitmap);

   AllegroFlare::TileMaps::PrimMeshAtlas atlas;
   atlas.duplicate_bitmap_and_load(source_bitmap, 12, 16, 0);

   std::vector<AllegroFlare::TileMaps::PrimMeshAtlasIndexRecord> tile_index = atlas.get_tile_index();
   //AllegroFlare::TileMaps::TileAtlasBuilder tile_atlas_builder(12, 16, tile_index);
   //ALLEGRO_BITMAP *result = tile_atlas_builder.create_extruded();
   ALLEGRO_BITMAP *result = AllegroFlare::TileMaps::TileAtlasBuilder::create_extruded(&tile_index);
   al_save_bitmap(build_test_filename_png("build__will_create_an_atlas_with_non_16x16_tiles").c_str(), result);

   al_destroy_bitmap(result);
   //atlas.clear();
   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}



TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   create_extruded__will_work_on_atlases_where_source_images_are_tall_or_wide_and_not_perfect_square_dimensions)
{
   // TODO
}



TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   create_scaled_and_extruded__will_create_a_pixel_perfect_scaled_atlas_with_tile_edges_extruded)
{
   // TODO
}



// TODO: Consider if this test needs to be located somewhere else
TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   DISABLED__get_tile_sub_bitmap__returns_the_sub_bitmap_of_the_tile)
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



TEST(AllegroFlare_TileMaps_TileAtlasBuilderTest,
   get_tile_sub_bitmap__when_a_tile_does_not_exist_at_that_index__returns_a_nullptr)
{
   // TODO
}


