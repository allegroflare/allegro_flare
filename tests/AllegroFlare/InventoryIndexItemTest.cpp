
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryIndexItem.hpp>


TEST(AllegroFlare_InventoryIndexItemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryIndexItem inventory_index_item;
}


TEST(AllegroFlare_InventoryIndexItemTest, to_tuple__returns_the_elements_as_a_tuple)
{
   AllegroFlare::InventoryIndexItem inventory_index_item("Item title", "bitmap_filename.png", "An item in the listing");
   std::tuple<std::string, std::string, std::string> expected_tuple(
      "Item title", "bitmap_filename.png", "An item in the listing");

   EXPECT_EQ(expected_tuple, inventory_index_item.to_tuple());
}


