
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/EnterRoom.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_EnterRoomTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom enter_room;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_EnterRoomTest, run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::EnterRoom enter_room;
   EXPECT_EQ("ScriptEventDatas/EnterRoom", enter_room.get_type());
}

