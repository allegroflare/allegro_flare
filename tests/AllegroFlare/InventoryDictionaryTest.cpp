
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryDictionary.hpp>


TEST(AllegroFlare_InventoryDictionaryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryDictionary inventory_dictionary;
}


TEST(AllegroFlare_InventoryDictionaryTest, exists__returns_true_if_the_id_exists_in_the_dictionary)
{
   AllegroFlare::InventoryDictionary inventory_dictionary({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 69, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(true, inventory_dictionary.exists(4));
   EXPECT_EQ(true, inventory_dictionary.exists(19));
   EXPECT_EQ(true, inventory_dictionary.exists(32));
   EXPECT_EQ(true, inventory_dictionary.exists(69));
}


TEST(AllegroFlare_InventoryDictionaryTest, exists__returns_false_if_the_id_does_not_exist_in_the_dictionary)
{
   AllegroFlare::InventoryDictionary inventory_dictionary({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 33, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(false, inventory_dictionary.exists(1));
   EXPECT_EQ(false, inventory_dictionary.exists(12));
   EXPECT_EQ(false, inventory_dictionary.exists(99));
}


TEST(AllegroFlare_InventoryDictionaryTest, size__returns_the_number_of_items_in_the_dictionary)
{
   AllegroFlare::InventoryDictionary inventory_dictionary({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 69, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(4, inventory_dictionary.size());
}


TEST(AllegroFlare_InventoryDictionaryTest, at__returns_the_inventory_dictionary_listing)
{
   AllegroFlare::InventoryDictionary inventory_dictionary({
     { 1, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 2, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 3, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 4, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   std::tuple<std::string, std::string, std::string> expected_listing = 
      { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." };

   EXPECT_EQ(expected_listing, inventory_dictionary.at(1).to_tuple());
}


TEST(AllegroFlare_InventoryDictionaryTest, at__if_the_item_does_not_exist__returns_an_empty_inventory_dictionary_item)
{
   AllegroFlare::InventoryDictionary inventory_dictionary({
     { 1, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 2, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 3, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 4, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(AllegroFlare::InventoryIndexItem("", "", "").to_tuple(), inventory_dictionary.at(99).to_tuple());
}


TEST(AllegroFlare_InventoryDictionaryTest,
   build_placeholder_inventory_dictionary__returns_an_inventory_dictionary_with_the_expected_items)
{
   std::map<int, AllegroFlare::InventoryIndexItem> expected_inventory_dictionary = {
     { 1, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
     { 2, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 3, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 4, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
   };

   AllegroFlare::InventoryDictionary built_placeholder_inventory_dictionary =
      AllegroFlare::InventoryDictionary::build_placeholder_inventory_dictionary();
   
   for (auto &expected_inventory_dictionary_item : expected_inventory_dictionary)
   {
      int key = expected_inventory_dictionary_item.first;
      AllegroFlare::InventoryIndexItem expected_item_listing = expected_inventory_dictionary_item.second;

      EXPECT_EQ(true, built_placeholder_inventory_dictionary.exists(key));
      EXPECT_EQ(expected_item_listing.to_tuple(), built_placeholder_inventory_dictionary.at(key).to_tuple());
   }
}

