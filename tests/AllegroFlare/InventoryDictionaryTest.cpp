
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryDictionary.hpp>

#include <AllegroFlare/InventoryDictionaryItems/ClassicItem.hpp>


class AllegroFlare_InventoryDictionaryTest: public ::testing::Test {};
class AllegroFlare_InventoryDictionaryTestWithDictionary : public ::testing::Test
{
public:
   AllegroFlare::InventoryDictionary inventory_dictionary;

   void SetUp()
   {
      using AllegroFlare::InventoryDictionaryItems::ClassicItem;

      inventory_dictionary.set_dictionary({
         { 4, new ClassicItem
            (
               "Toy Train",
               "toy-train-02.png",
               "It sure has a lot of detail."
            )
         },
         { 19, new ClassicItem
            (
               "Metal Pipe",
               "metal-pipe-01.png",
               "Made of galvanized metal, this pipe is very sturdy."
            )
         },
         { 32, new ClassicItem
            (
               "Blaster",
               "blaster-02.png",
               "Standard issue weaponry."
            )
         },
         { 69, new ClassicItem
            (
               "Walkie-Talkie",
               "walkie-02.png",
               "A small portable radio to communicate with someone far away."
            )
         },
      });
   }
};


TEST_F(AllegroFlare_InventoryDictionaryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryDictionary inventory_dictionary;
}


TEST_F(AllegroFlare_InventoryDictionaryTestWithDictionary,
   exists__returns_true_if_the_id_exists_in_the_dictionary)
{
   EXPECT_EQ(true, inventory_dictionary.exists(4));
   EXPECT_EQ(true, inventory_dictionary.exists(19));
   EXPECT_EQ(true, inventory_dictionary.exists(32));
   EXPECT_EQ(true, inventory_dictionary.exists(69));
}


TEST_F(AllegroFlare_InventoryDictionaryTestWithDictionary,
   exists__returns_false_if_the_id_does_not_exist_in_the_dictionary)
{
   EXPECT_EQ(false, inventory_dictionary.exists(1));
   EXPECT_EQ(false, inventory_dictionary.exists(12));
   EXPECT_EQ(false, inventory_dictionary.exists(33));
}


TEST_F(AllegroFlare_InventoryDictionaryTestWithDictionary, size__returns_the_number_of_items_in_the_dictionary)
{
   EXPECT_EQ(4, inventory_dictionary.size());
}


TEST_F(AllegroFlare_InventoryDictionaryTestWithDictionary, at__returns_the_inventory_dictionary_listing)
{
   std::tuple<std::string, std::string, std::string> expected_listing = {
      "Toy Train", "toy-train-02.png", "It sure has a lot of detail."
   };

   AllegroFlare::InventoryDictionaryItems::Base* item = inventory_dictionary.at(4);
   ASSERT_NE(nullptr, item);
   AllegroFlare::InventoryDictionaryItems::ClassicItem* item_as_classic_item =
      static_cast<AllegroFlare::InventoryDictionaryItems::ClassicItem*>(item);
   EXPECT_EQ(expected_listing, item_as_classic_item->to_tuple());
}


TEST_F(AllegroFlare_InventoryDictionaryTestWithDictionary, at__if_the_item_does_not_exist__returns_a_nullptr)
{
   EXPECT_EQ(nullptr, inventory_dictionary.at(99));
}


TEST_F(AllegroFlare_InventoryDictionaryTest,
   DISABLED__build_placeholder_inventory_dictionary__returns_an_inventory_dictionary_with_the_expected_items)
{
   using AllegroFlare::InventoryDictionaryItems::ClassicItem;

   std::map<int, AllegroFlare::InventoryDictionaryItems::Base*> expected_inventory_dictionary = {
      { 1, new ClassicItem
         (
            "Walkie-Talkie",
            "walkie-02.png",
            "A small portable radio to communicate with someone far away."
         )
      },
      { 2, new ClassicItem
         (
            "Blaster",
            "blaster-02.png",
            "Standard issue weaponry."
         )
      },
      { 3, new ClassicItem
         (
            "Train",
            "toy-train-02.png",
            "It sure has a lot of detail."
         )
      },
      { 4, new ClassicItem
         (
            "Metal Pipe",
            "metal-pipe-01.png",
            "Made of galvanized metal, this pipe is very sturdy."
         )
      },
   };

   AllegroFlare::InventoryDictionary built_placeholder_inventory_dictionary =
      AllegroFlare::InventoryDictionary::build_placeholder_inventory_dictionary();
   
   for (auto &expected_inventory_dictionary_item : expected_inventory_dictionary)
   {
      //int key = expected_inventory_dictionary_item.first;
      //AllegroFlare::InventoryIndexItem expected_item_listing = expected_inventory_dictionary_item.second;

      //EXPECT_EQ(true, built_placeholder_inventory_dictionary.exists(key));
      //EXPECT_EQ(expected_item_listing.to_tuple(), built_placeholder_inventory_dictionary.at(key).to_tuple());
   }
}

