
#include <gtest/gtest.h>

#include <AllegroFlare/StableVector.hpp>
#include <AllegroFlare/Physics/CollisionMeshFace.hpp>



TEST(AllegroFlare_StableVectorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::StableVector<std::string> stable_vector;
}


//TEST(AllegroFlare_StableVectorTest, can_be_created_without_blowing_up_2)
//{
   //AllegroFlare::StableVector<AllegroFlare::Physics::CollisionMeshFace> stable_vector;
//}


TEST(AllegroFlare_StableVectorTest, add__will_add_elements)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("Hello");
   auto key2 = stable_vector.add("World");

   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_EQ(stable_vector.get(key1), "Hello");
   EXPECT_EQ(stable_vector.get(key2), "World");
}


TEST(AllegroFlare_StableVectorTest, contains__will_return_true_if_the_element_exists)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("First");
   auto key2 = stable_vector.add("Second");

   stable_vector.remove(key1);

   EXPECT_EQ(1, stable_vector.size());
   EXPECT_EQ(false, stable_vector.contains(key1));
   EXPECT_EQ(true, stable_vector.contains(key2));
   EXPECT_EQ("Second", stable_vector.get(key2));
}


TEST(AllegroFlare_StableVectorTest, CanAccessByKey)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("A");
   auto key2 = stable_vector.add("B");

   EXPECT_NO_THROW({
      EXPECT_EQ(stable_vector.get(key1), "A");
      EXPECT_EQ(stable_vector.get(key2), "B");
   });

   EXPECT_THROW(stable_vector.get(999), std::out_of_range);
}


TEST(AllegroFlare_StableVectorTest, SwapAndPopRemovesCorrectly)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("Element1");
   auto key2 = stable_vector.add("Element2");
   auto key3 = stable_vector.add("Element3");

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


TEST(AllegroFlare_StableVectorTest, CanCheckContainment)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("Existential");
   EXPECT_TRUE(stable_vector.contains(key1));

   stable_vector.remove(key1);
   EXPECT_FALSE(stable_vector.contains(key1));
}


TEST(AllegroFlare_StableVectorTest, HandlesEmptyContainer)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_FALSE(stable_vector.contains(0));

   EXPECT_THROW(stable_vector.get(0), std::out_of_range);
}


TEST(AllegroFlare_StableVectorTest, RetainsContiguousNatureAfterModifications)
{
   AllegroFlare::StableVector<std::string> stable_vector;
   auto key1 = stable_vector.add("First");
   auto key2 = stable_vector.add("Second");
   auto key3 = stable_vector.add("Third");

   // Remove and add elements
   stable_vector.remove(key2);
   auto key4 = stable_vector.add("Fourth");

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


TEST(AllegroFlare_StableVectorTest, BuildMethodProvidesSlotAndAllowsModification)
{
   AllegroFlare::StableVector<std::string> stable_vector;

   // Add an uninitialized slot and modify it
   auto [key1, value1] = stable_vector.allocate();
   value1 = "Hello";

   // Verify the built value
   EXPECT_EQ(stable_vector.size(), 1);
   EXPECT_TRUE(stable_vector.contains(key1));
   EXPECT_EQ(stable_vector.get(key1), "Hello");

   // Add another slot and modify it
   auto [key2, value2] = stable_vector.allocate();
   value2 = "World";

   // Verify the second value
   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_TRUE(stable_vector.contains(key2));
   EXPECT_EQ(stable_vector.get(key2), "World");

   // Ensure the first value is still intact
   EXPECT_EQ(stable_vector.get(key1), "Hello");
}


