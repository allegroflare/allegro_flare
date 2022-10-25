#include <gtest/gtest.h>

#include <AllegroFlare/Inventory.hpp>


TEST(AllegroFlare_InventoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Inventory inventory;
}


TEST(AllegroFlare_InventoryTest, add_item__will_append_an_item_to_the_list_of_items)
{
   AllegroFlare::Inventory inventory;
   std::vector<int> expected_items;

   inventory.add_item(3);

   expected_items = { 3 };
   EXPECT_EQ(expected_items, inventory.get_items_ref());

   inventory.add_item(5);

   expected_items = { 3, 5 };
   EXPECT_EQ(expected_items, inventory.get_items_ref());
}


TEST(AllegroFlare_InventoryTest, add_items__will_append_items_to_the_list_of_items)
{
   AllegroFlare::Inventory inventory;
   inventory.add_item(1);
   inventory.add_item(2);
   inventory.add_item(3);

   std::vector<int> expected_items = { 1, 2, 3, 7, 82, 32 };

   inventory.add_items({ 7, 82, 32 });
   EXPECT_EQ(expected_items, inventory.get_items_ref());
}



