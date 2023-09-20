
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/CloseDialog.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CloseDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog close_dialog;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CloseDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/CloseDialog",
     AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CloseDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog close_dialog;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::CloseDialog::TYPE, close_dialog.get_type());
}


