
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>


TEST(AllegroFlare_DialogTree_NodeOptions_ExitDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::NodeOptions::ExitDialog exit_dialog;
}


TEST(AllegroFlare_DialogTree_NodeOptions_ExitDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/NodeOptions/ExitDialog",
     AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE
   );
}


TEST(AllegroFlare_DialogTree_NodeOptions_ExitDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::NodeOptions::ExitDialog exit_dialog;
   EXPECT_EQ(AllegroFlare::DialogTree::NodeOptions::ExitDialog::TYPE, exit_dialog.get_type());
}


