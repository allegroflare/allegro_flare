
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotAnItemDialog.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotAnItemDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog create_you_got_an_item_dialog;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotAnItemDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotAnItemDialog",
     AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotAnItemDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog create_you_got_an_item_dialog;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotAnItemDialog::TYPE, create_you_got_an_item_dialog.get_type());
}


