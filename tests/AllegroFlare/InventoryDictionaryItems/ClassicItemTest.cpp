
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryDictionaryItems/ClassicItem.hpp>


TEST(AllegroFlare_InventoryDictionaryItems_ClassicItemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryDictionaryItems::ClassicItem classic_item;
}


TEST(AllegroFlare_InventoryDictionaryItems_ClassicItemTest, TYPE__has_the_expected_value)
{
   AllegroFlare::InventoryDictionaryItems::ClassicItem classic_item;
   EXPECT_EQ("InventoryDictionaryItems/ClassicItem", classic_item.get_type());
}


TEST(AllegroFlare_InventoryDictionaryItems_ClassicItemTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::InventoryDictionaryItems::ClassicItem classic_item;
   EXPECT_EQ(AllegroFlare::InventoryDictionaryItems::ClassicItem::TYPE, classic_item.get_type());
}


