
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
}


TEST(AllegroFlare_Prototypes_MindDive_TunnelMeshTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::MindDive::TunnelMesh tunnel_mesh;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, tunnel_mesh.run());
}


