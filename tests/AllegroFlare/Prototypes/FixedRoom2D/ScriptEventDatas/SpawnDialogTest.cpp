
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/SpawnDialog.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_SpawnDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::SpawnDialog spawn_dialog;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_SpawnDialogTest, has_the_expected_type)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::SpawnDialog spawn_dialog;
   EXPECT_EQ("ScriptEventDatas/SpawnDialog", spawn_dialog.get_type());
}


// TODO: add test for TYPE constant matching expected string
// TODO: add test for type matching constant TYPE


