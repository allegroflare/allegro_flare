
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/EmitGameEvent.hpp>


TEST(AllegroFlare_DialogTree_Nodes_EmitGameEventTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::EmitGameEvent emit_game_event;
}


TEST(AllegroFlare_DialogTree_Nodes_EmitGameEventTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/EmitGameEvent",
     AllegroFlare::DialogTree::Nodes::EmitGameEvent::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_EmitGameEventTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::EmitGameEvent emit_game_event;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::EmitGameEvent::TYPE, emit_game_event.get_type());
}


