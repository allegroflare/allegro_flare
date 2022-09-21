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


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, initialize__without_allegro_initialized__raises_an_error)
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
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
   tunnel_mesh.initialize();
   tunnel_mesh.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Prototypes_MindDive_TunnelMeshTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_mesh_as_expected)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
   tunnel_mesh.initialize();

   AllegroFlare::Placement2D place;
   //place.scale = {16, 16};

   clear();

   place.start_transform();
   tunnel_mesh.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


