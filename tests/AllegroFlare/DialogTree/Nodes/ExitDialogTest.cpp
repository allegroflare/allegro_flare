
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>


TEST(AllegroFlare_DialogTree_Nodes_ExitDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::ExitDialog exit_dialog;
}


TEST(AllegroFlare_DialogTree_Nodes_ExitDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/ExitDialog",
     AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_ExitDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::ExitDialog exit_dialog;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::ExitDialog::TYPE, exit_dialog.get_type());
}


