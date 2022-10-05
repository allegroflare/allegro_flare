#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Prototypes_MindDive_TunnelMeshTest : public ::testing::Test {};
class AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/Camera3D.hpp>


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, DISABLED__initialize__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
   std::string expected_error_message =
      "TunnelMesh::initialize: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(tunnel_mesh.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, render__before_being_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
   std::string expected_error_message =
      "TunnelMesh::render: error: guard \"initialized\" not met";
   EXPECT_THROW_WITH_MESSAGE(tunnel_mesh.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh(&get_bitmap_bin_ref());
   tunnel_mesh.set_atlas_configuration("uv.png", 100, 100);
   tunnel_mesh.initialize();
   tunnel_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_mesh_as_expected)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh(&get_bitmap_bin_ref());
   tunnel_mesh.set_atlas_configuration("uv.png", 100, 100);
   tunnel_mesh.initialize();

   tunnel_mesh.resize(12, 32);
   tunnel_mesh.random_fill();

   AllegroFlare::Camera3D camera;
   camera.position = AllegroFlare::Vec3D(5.5, 0, 0);
   camera.stepout = AllegroFlare::Vec3D(0, 0, 10);
   camera.tilt = 0.4;

   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));
   clear();
   tunnel_mesh.render();
   al_flip_display();

   //sleep_for(1);
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture,
   obtain_num_rows__will_return_the_number_of_rows_in_the_tunnel_mesh)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture,
   obtain_num_columns__will_return_the_number_of_columns_in_the_tunnel_mesh)
{
   // TODO
}


