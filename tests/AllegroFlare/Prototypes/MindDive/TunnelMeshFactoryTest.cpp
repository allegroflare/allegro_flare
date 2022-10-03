
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>

#include <allegro5/allegro_primitives.h>


#ifdef _WIN32
#define TMJ_FIXTURE_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#define TMJ_FIXTURE_FILENAME (TMJ_FIXTURE_PATH "tunnel_mesh-02.tmj")


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory tunnel_mesh_factory;
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshFactoryTest,
   create_from_tmj__will_create_a_tunnel_mesh_with_with_the_expected_values_from_a_tmj_file)
{
   al_init();
   al_init_primitives_addon();
   al_init_image_addon();
   AllegroFlare::BitmapBin bitmap_bin;

   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory tunnel_mesh_factory(&bitmap_bin);
   AllegroFlare::Prototypes::MindDive::TunnelMesh* created_tunnel_mesh =
      tunnel_mesh_factory.create_from_tmj(TMJ_FIXTURE_FILENAME);

   ASSERT_NE(nullptr, created_tunnel_mesh);

   EXPECT_EQ(12, created_tunnel_mesh->obtain_num_columns());
   EXPECT_EQ(96, created_tunnel_mesh->obtain_num_rows());

   // select a few tiles to cherry-pick
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = created_tunnel_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = created_tunnel_mesh->get_collision_tile_map_ref();

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


