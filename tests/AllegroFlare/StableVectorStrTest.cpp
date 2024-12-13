
#include <gtest/gtest.h>

#include <AllegroFlare/StableVectorStr.hpp> // Replace with the correct header for StableVectorStr


TEST(AllegroFlare_StableVectorStrTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
}


TEST(AllegroFlare_StableVectorStrTest, add__will_add_elements)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "Hello");
   auto key2 = stable_vector.add("key2", "World");

   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_EQ(stable_vector.get(key1), "Hello");
   EXPECT_EQ(stable_vector.get(key2), "World");
}


TEST(AllegroFlare_StableVectorStrTest, contains__will_return_true_if_the_element_exists)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "First");
   auto key2 = stable_vector.add("key2", "Second");

   stable_vector.remove(key1);

   EXPECT_EQ(1, stable_vector.size());
   EXPECT_EQ(false, stable_vector.contains(key1));
   EXPECT_EQ(true, stable_vector.contains(key2));
   EXPECT_EQ("Second", stable_vector.get(key2));
}


TEST(AllegroFlare_StableVectorStrTest, CanAccessByKey)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "A");
   auto key2 = stable_vector.add("key2", "B");

   EXPECT_NO_THROW({
      EXPECT_EQ(stable_vector.get(key1), "A");
      EXPECT_EQ(stable_vector.get(key2), "B");
   });

   EXPECT_THROW(stable_vector.get("nonexistent_key"), std::out_of_range);
}


TEST(AllegroFlare_StableVectorStrTest, SwapAndPopRemovesCorrectly)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "Element1");
   auto key2 = stable_vector.add("key2", "Element2");
   auto key3 = stable_vector.add("key3", "Element3");

   // Remove the middle element
   stable_vector.remove(key2);

   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_FALSE(stable_vector.contains(key2));
   EXPECT_TRUE(stable_vector.contains(key1));
   EXPECT_TRUE(stable_vector.contains(key3));

   // Validate the remaining keys
   EXPECT_EQ(stable_vector.get(key1), "Element1");
   EXPECT_EQ(stable_vector.get(key3), "Element3");
}


TEST(AllegroFlare_StableVectorStrTest, CanCheckContainment)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "Existential");
   EXPECT_TRUE(stable_vector.contains(key1));

   stable_vector.remove(key1);
   EXPECT_FALSE(stable_vector.contains(key1));
}


TEST(AllegroFlare_StableVectorStrTest, HandlesEmptyContainer)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_FALSE(stable_vector.contains("key1"));

   EXPECT_THROW(stable_vector.get("key1"), std::out_of_range);
}


TEST(AllegroFlare_StableVectorStrTest, RetainsContiguousNatureAfterModifications)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "First");
   auto key2 = stable_vector.add("key2", "Second");
   auto key3 = stable_vector.add("key3", "Third");

   // Remove and add elements
   stable_vector.remove(key2);
   auto key4 = stable_vector.add("key4", "Fourth");

   // Retrieve the data vector
   const auto &data = stable_vector.get_data();

   // Verify the vector is contiguous
   EXPECT_EQ(&data[1], &data[0] + 1); // Second element is directly after the first
   EXPECT_EQ(&data[2], &data[1] + 1); // Third element is directly after the second

   // Validate the contents
   EXPECT_EQ(data.size(), 3); // Only 3 elements remain
   EXPECT_EQ(data[0], "First");
   EXPECT_EQ(data[1], "Third"); // "Third" was swapped to index 1 after removal of "Second"
   EXPECT_EQ(data[2], "Fourth");
}


TEST(AllegroFlare_StableVectorStrTest, BuildMethodProvidesSlotAndAllowsModification)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;

   // Add an uninitialized slot and modify it
   auto &value1 = stable_vector.allocate("key1");
   value1 = "Hello";

   // Verify the built value
   EXPECT_EQ(stable_vector.size(), 1);
   EXPECT_TRUE(stable_vector.contains("key1"));
   EXPECT_EQ(stable_vector.get("key1"), "Hello");

   // Add another slot and modify it
   auto &value2 = stable_vector.allocate("key2");
   value2 = "World";

   // Verify the second value
   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_TRUE(stable_vector.contains("key2"));
   EXPECT_EQ(stable_vector.get("key2"), "World");

   // Ensure the first value is still intact
   EXPECT_EQ(stable_vector.get("key1"), "Hello");
}


