
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


