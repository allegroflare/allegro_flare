#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Prototypes_TileDrive_TerrainMeshTest : public ::testing::Test {};
class AllegroFlare_Prototypes_TileDrive_TerrainMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Camera3D.hpp>


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMesh terrain_mesh;
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTest, DISABLED__initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMesh terrain_mesh;
   std::string expected_error_message =
      "TerrainMesh::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(terrain_mesh.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTest, render__before_being_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::TileDrive::TerrainMesh terrain_mesh;
   std::string expected_error_message =
      "TerrainMesh::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(terrain_mesh.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMesh terrain_mesh(&get_bitmap_bin_ref());
   terrain_mesh.set_atlas_configuration("uv.png", 100, 100);
   terrain_mesh.initialize();
   terrain_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_mesh_as_expected)
{
   AllegroFlare::Prototypes::TileDrive::TerrainMesh terrain_mesh(&get_bitmap_bin_ref());
   terrain_mesh.set_atlas_configuration("uv.png", 100, 100);
   terrain_mesh.initialize();

   terrain_mesh.resize(12, 32);
   terrain_mesh.random_fill();

   AllegroFlare::Camera3D camera;
   camera.position = AllegroFlare::Vec3D(5.5, 0, 0);
   camera.stepout = AllegroFlare::Vec3D(0, 0, 10);
   camera.tilt = 0.4;

   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));
   clear();
   terrain_mesh.render();
   al_flip_display();

   //sleep_for(1);
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTestWithAllegroRenderingFixture,
   obtain_num_rows__will_return_the_number_of_rows_in_the_terrain_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TerrainMeshTestWithAllegroRenderingFixture,
   obtain_num_columns__will_return_the_number_of_columns_in_the_terrain_mesh)
{
   // TODO
}


