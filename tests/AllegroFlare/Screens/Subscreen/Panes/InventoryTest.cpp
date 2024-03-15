
#include <gtest/gtest.h>

#include <AllegroFlare/Screens/Subscreen/Panes/Inventory.hpp>


TEST(AllegroFlare_Screens_Subscreen_Panes_InventoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Subscreen::Panes::Inventory inventory;
}


TEST(AllegroFlare_Screens_Subscreen_Panes_InventoryTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Screens/Subscreen/Panes/Inventory",
     AllegroFlare::Screens::Subscreen::Panes::Inventory::TYPE
   );
}


TEST(AllegroFlare_Screens_Subscreen_Panes_InventoryTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Screens::Subscreen::Panes::Inventory inventory;
   EXPECT_EQ(AllegroFlare::Screens::Subscreen::Panes::Inventory::TYPE, inventory.get_type());
}


