
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryDictionaryItems/Base.hpp>


class InventoryDictionaryItemsBaseTestClass : public AllegroFlare::InventoryDictionaryItems::Base
{
public:
   InventoryDictionaryItemsBaseTestClass()
      : AllegroFlare::InventoryDictionaryItems::Base("InventoryDictionaryItemsBaseTestClass")
   {}
};


TEST(AllegroFlare_InventoryDictionaryItems_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryDictionaryItems::Base base;
}


TEST(AllegroFlare_InventoryDictionaryItems_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::InventoryDictionaryItems::Base base;
   EXPECT_EQ("InventoryDictionaryItems/Base", base.get_type());
}


TEST(AllegroFlare_InventoryDictionaryItems_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::InventoryDictionaryItems::Base base;
   EXPECT_EQ(AllegroFlare::InventoryDictionaryItems::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_InventoryDictionaryItems_BaseTest, derived_classes_will_have_the_expected_type)
{
   InventoryDictionaryItemsBaseTestClass test_class;
   EXPECT_EQ("InventoryDictionaryItemsBaseTestClass", test_class.get_type());
}


