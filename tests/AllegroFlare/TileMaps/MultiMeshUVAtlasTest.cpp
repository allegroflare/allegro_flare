
#include <gtest/gtest.h>

#include <AllegroFlare/TileMaps/MultiMeshUVAtlas.hpp>


TEST(AllegroFlare_TileMaps_MultiMeshUVAtlasTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TileMaps::MultiMeshUVAtlas multi_mesh_uvatlas;
}


TEST(AllegroFlare_TileMaps_MultiMeshUVAtlasTest, exists__will_return_true_if_an_item_exists)
{
   AllegroFlare::TileMaps::MultiMeshUVAtlas multi_mesh_uvatlas;
   multi_mesh_uvatlas.add(321, 0.0, 1.0, 2.0, 4.0);
   EXPECT_EQ(true, multi_mesh_uvatlas.exists(321));
}


TEST(AllegroFlare_TileMaps_MultiMeshUVAtlasTest, exists__will_return_false_if_an_item_does_not_exist_at_the_index)
{
   AllegroFlare::TileMaps::MultiMeshUVAtlas multi_mesh_uvatlas;
   EXPECT_EQ(false, multi_mesh_uvatlas.exists(321));
}


