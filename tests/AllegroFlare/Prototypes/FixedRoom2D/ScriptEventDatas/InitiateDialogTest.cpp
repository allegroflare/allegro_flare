
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/InitiateDialog.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_InitiateDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog spawn_dialog;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_InitiateDialogTest, has_the_expected_type)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::InitiateDialog spawn_dialog;
   EXPECT_EQ("ScriptEventDatas/InitiateDialog", spawn_dialog.get_type());
}


// TODO: add test for TYPE constant matching expected string
// TODO: add test for type matching constant TYPE


