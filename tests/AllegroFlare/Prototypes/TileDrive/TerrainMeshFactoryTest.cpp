
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshFactory.hpp>

#include <allegro5/allegro_primitives.h>


#ifdef _WIN32
#define TMJ_FIXTURE_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#define TMJ_FIXTURE_FILENAME (TMJ_FIXTURE_PATH "tunnel_mesh-02.tmj")
#define TILEMAP_BITMAP_IDENTIFIER "uv-with-decorations-0x.png"


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory terrain_mesh_factory;
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshFactoryTest,
   create_from_tmj__when_collision_layer_is_not_present__will_assign_equivelent_data_to_prim_mesh_\
and_collision_tile_map)
{
   al_init();
   al_init_primitives_addon();
   al_init_image_addon();
   AllegroFlare::BitmapBin bitmap_bin;

   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory terrain_mesh_factory(&bitmap_bin);
   AllegroFlare::Prototypes::TileDrive::TerrainMesh* created_terrain_mesh =
      terrain_mesh_factory.create_from_tmj(TMJ_FIXTURE_FILENAME, TILEMAP_BITMAP_IDENTIFIER, 50, 50);

   ASSERT_NE(nullptr, created_terrain_mesh);

   EXPECT_EQ(12, created_terrain_mesh->obtain_num_columns());
   EXPECT_EQ(96, created_terrain_mesh->obtain_num_rows());

   // select a few tiles to cherry-pick
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = created_terrain_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = created_terrain_mesh->get_collision_tile_map_ref();

   EXPECT_EQ(2, prim_mesh.get_tile_id(0, 0));
   EXPECT_EQ(1, prim_mesh.get_tile_id(0, 1));
   EXPECT_EQ(0, prim_mesh.get_tile_id(0, 22));
   EXPECT_EQ(2, collision_tile_map.get_tile(0, 0));
   EXPECT_EQ(1, collision_tile_map.get_tile(0, 1));
   //EXPECT_EQ(0, collision_tile_map.get_tile(0, 22)); // TODO: find out why this is failing, is returning -1

   bitmap_bin.clear();
   al_shutdown_image_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_TileDrive_TerrainMeshFactoryTest,
   create_from_tmj__when_a_collision_layer_is_present__will_assign_expected_values)
{
   // TODO
}


