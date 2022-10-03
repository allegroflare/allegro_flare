
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>

#include <allegro5/allegro_primitives.h>

#ifdef _WIN32
//#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
//#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
#else
//#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
//#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
#endif

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
   AllegroFlare::Prototypes::MindDive::TunnelMesh* created_tunnel_mesh = tunnel_mesh_factory.create_from_tmj();

   ASSERT_NE(nullptr, created_tunnel_mesh);

   bitmap_bin.clear();
   al_shutdown_image_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


