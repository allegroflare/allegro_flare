
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryDictionaryItems/WithAttributes.hpp>


TEST(AllegroFlare_InventoryDictionaryItems_WithAttributesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryDictionaryItems::WithAttributes with_attributes;
}


TEST(AllegroFlare_InventoryDictionaryItems_WithAttributesTest, TYPE__has_the_expected_value)
{
   AllegroFlare::InventoryDictionaryItems::WithAttributes with_attributes;
   EXPECT_EQ("InventoryDictionaryItems/WithAttributes", with_attributes.get_type());
}


TEST(AllegroFlare_InventoryDictionaryItems_WithAttributesTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::InventoryDictionaryItems::WithAttributes with_attributes;
   EXPECT_EQ(AllegroFlare::InventoryDictionaryItems::WithAttributes::TYPE, with_attributes.get_type());
}


