
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/EnterScene.hpp>


TEST(AllegroFlare_DialogTree_Nodes_EnterSceneTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::EnterScene enter_scene;
}


TEST(AllegroFlare_DialogTree_Nodes_EnterSceneTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/EnterScene",
     AllegroFlare::DialogTree::Nodes::EnterScene::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_EnterSceneTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::EnterScene enter_scene;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::EnterScene::TYPE, enter_scene.get_type());
}


