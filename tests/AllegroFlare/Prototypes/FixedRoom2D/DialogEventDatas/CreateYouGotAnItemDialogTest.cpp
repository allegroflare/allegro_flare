
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotAnItemDialog.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotAnItemDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotAnItemDialog create_you_got_an_item_dialog;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotAnItemDialogTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotAnItemDialog create_you_got_an_item_dialog;
   EXPECT_EQ("DialogEventDatas/CreateYouGotAnItemDialog", create_you_got_an_item_dialog.get_type());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotAnItemDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotAnItemDialog create_you_got_an_item_dialog;
   EXPECT_EQ(AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotAnItemDialog::TYPE, create_you_got_an_item_dialog.get_type());
}


