
#include <gtest/gtest.h>

#include <AllegroFlare/InventoryIndex.hpp>


TEST(AllegroFlare_InventoryIndexTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InventoryIndex inventory_index;
}


TEST(AllegroFlare_InventoryIndexTest, exists__returns_true_if_the_id_exists_in_the_index)
{
   AllegroFlare::InventoryIndex inventory_index({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 69, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(true, inventory_index.exists(4));
   EXPECT_EQ(true, inventory_index.exists(19));
   EXPECT_EQ(true, inventory_index.exists(32));
   EXPECT_EQ(true, inventory_index.exists(69));
}


TEST(AllegroFlare_InventoryIndexTest, exists__returns_false_if_the_id_does_not_exist_in_the_index)
{
   AllegroFlare::InventoryIndex inventory_index({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 33, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(false, inventory_index.exists(1));
   EXPECT_EQ(false, inventory_index.exists(12));
   EXPECT_EQ(false, inventory_index.exists(99));
}


TEST(AllegroFlare_InventoryIndexTest, size__returns_the_number_of_items_in_the_index)
{
   AllegroFlare::InventoryIndex inventory_index({
     { 4, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 19, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 32, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 69, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(4, inventory_index.size());
}


TEST(AllegroFlare_InventoryIndexTest, at__returns_the_inventory_index_listing)
{
   AllegroFlare::InventoryIndex inventory_index({
     { 1, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 2, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 3, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 4, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   std::tuple<std::string, std::string, std::string> expected_listing = 
      { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." };

   EXPECT_EQ(expected_listing, inventory_index.at(1).to_tuple());
}


TEST(AllegroFlare_InventoryIndexTest, at__if_the_item_does_not_exist__returns_an_empty_inventory_index_item)
{
   AllegroFlare::InventoryIndex inventory_index({
     { 1, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 2, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 3, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 4, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
   });

   EXPECT_EQ(AllegroFlare::InventoryIndexItem("", "", "").to_tuple(), inventory_index.at(99).to_tuple());
}


TEST(AllegroFlare_InventoryIndexTest,
   build_placeholder_inventory_index__returns_an_inventory_index_with_the_expected_items)
{
   std::map<int, AllegroFlare::InventoryIndexItem> expected_inventory_index = {
     { 1, { "Walkie-Talkie", "walkie-02.png", "A small portable radio to communicate with someone far away." } },
     { 2, { "Blaster", "blaster-02.png", "Standard issue weaponry." } },
     { 3, { "Toy Train", "toy-train-02.png", "It sure has a lot of detail." } },
     { 4, { "Metal Pipe", "metal-pipe-01.png", "Made of galvanized metal, this pipe is very sturdy." } },
     { 5, { "Robot Helmet", "robot_helmet-01.png", "Features integrated sensors and communication modules." } },
   };

   AllegroFlare::InventoryIndex built_placeholder_inventory_index =
      AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   
   for (auto &expected_inventory_index_item : expected_inventory_index)
   {
      int key = expected_inventory_index_item.first;
      AllegroFlare::InventoryIndexItem expected_item_listing = expected_inventory_index_item.second;

      EXPECT_EQ(true, built_placeholder_inventory_index.exists(key));
      EXPECT_EQ(expected_item_listing.to_tuple(), built_placeholder_inventory_index.at(key).to_tuple());
   }
}


