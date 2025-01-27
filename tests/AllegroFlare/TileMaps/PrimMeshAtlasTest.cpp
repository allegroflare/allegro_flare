


// NOTE: Most of these tests come from an earlier factoring and have not been updated. Most contain test names
// of previous classes. Feel free to clean it up.

// TODO: Update the test names
// TODO: Ensure the test subjects are indeed the PrimMeshAatlas



#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_TileMaps_PrimMeshAtlasTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::PrimMeshAtlas prim_mesh_atlas;
}





// TODO: Previously, the destructor had this warning:

   //std::cout << "[~PrimMeshAtlas()] WARNING: tile atlas may contain a bitmap (and potentially depenedencies "
             //<< "reliant on it) that has not been properly freed. This destruction mechanism has not yet "
             //<< "been properly implemented."
             //<< std::endl;

// Consider its ramifications







#include <gtest/gtest.h>

//#include <Tileo/TileAtlasBuilder.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>

#define TEMP_TEST_FILE_PATH "/Users/markoates/Repos/allegro_flare/tmp/tests/"
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
#define TEST_TILE_ATLAS_BITMAP_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/tiles_dungeon_v1.1.png"
#else
#define TEST_TILE_ATLAS_BITMAP_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/tiles_dungeon_v1.1.png"
#endif


static std::string build_test_filename_png(std::string test_name)
{
   return TEMP_TEST_FILE_PATH + test_name + ".png";
}


TEST(AllegroFlare_TileMaps_PrimMeshAtlas_TileAtlasBuilderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::TileAtlasBuilder tile_atlast_builder;
}


TEST(AllegroFlare_TileMaps_PrimMeshAtlas_TileAtlasBuilderTest,
   get_tile_sub_bitmap__returns_the_sub_bitmap_of_the_tile)
{
   al_init();
   al_init_image_addon();
   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
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


TEST(AllegroFlare_TileMaps_PrimMeshAtlas_TileAtlasBuilderTest,
   on_destruction__when_initialized_but_not_destroyed__will_output_a_warning_message)
{
   al_init();
   al_init_image_addon();
   ALLEGRO_BITMAP* source_bitmap = al_load_bitmap(TEST_TILE_ATLAS_BITMAP_PATH);
   ASSERT_NE(nullptr, source_bitmap);

   AllegroFlare::TileMaps::PrimMeshAtlas *atlas = new AllegroFlare::TileMaps::PrimMeshAtlas;
   atlas->duplicate_bitmap_and_load(source_bitmap, 16, 16, 0); // Initializes the atlas

   //testing::internal::CaptureStdout();
   EXPECT_STDOUT(
      delete atlas, 
   //std::string expected_cout_output =
      "\x1B[1;33m[AllegroFlare::TileMaps::PrimMeshAtlas::~destroy]: "
         "warning: The class was initialized but not destroyed. This likely means that a dangling pointer "
         "was left, please review.\x1B[0m\n"
   );

   //std::string actual_cout_output = testing::internal::GetCapturedStdout();
   //EXPECT_EQ(expected_cout_output, actual_cout_output);

   al_destroy_bitmap(source_bitmap);
   al_shutdown_image_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_TileMaps_PrimMeshAtlas_TileAtlasBuilderTest,
   get_tile_sub_bitmap__when_a_tile_does_not_exist_at_that_index__returns_a_nullptr)
{
   // TODO
}


TEST(AllegroFlare_TileMaps_PrimMeshAtlasTest, get_sub_bitmap__returns_the_sub_bitmap_of_the_tile)
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



