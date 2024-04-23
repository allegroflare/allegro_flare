
#include <gtest/gtest.h>

#include <AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog.hpp>


TEST(AllegroFlare_DialogTree_Nodes_YouGotAnItemDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog you_got_an_item_dialog;
}


TEST(AllegroFlare_DialogTree_Nodes_YouGotAnItemDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogTree/Nodes/YouGotAnItemDialog",
     AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE
   );
}


TEST(AllegroFlare_DialogTree_Nodes_YouGotAnItemDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog node;
   EXPECT_EQ(AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog::TYPE, node.get_type());
}


