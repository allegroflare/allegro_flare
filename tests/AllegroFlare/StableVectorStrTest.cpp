
#include <gtest/gtest.h>

#include <AllegroFlare/StableVectorStr.hpp>


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
}


TEST(AllegroFlare_StableVectorStrTest, add__on_a_key_that_already_exists__will_throw_an_error)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.add("existing_key", "Initial Value");
   EXPECT_THROW(stable_vector.allocate("existing_key"), std::invalid_argument);
}


TEST(AllegroFlare_StableVectorStrTest, contains__will_return_true_if_the_element_exists)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "First");
   EXPECT_EQ(true, stable_vector.contains(key1));
}


TEST(AllegroFlare_StableVectorStrTest, contains__will_return_false_if_the_element_does_not_exist)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_EQ(false, stable_vector.contains("nonexistent_key"));
}


TEST(AllegroFlare_StableVectorStrTest, get__will_return_the_value_of_the_element)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "A");
   auto key2 = stable_vector.add("key2", "B");

   EXPECT_EQ(stable_vector.get(key1), "A");
   EXPECT_EQ(stable_vector.get(key2), "B");
}


TEST(AllegroFlare_StableVectorStrTest, get__when_no_key_is_present__will_throw_an_error)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_THROW(stable_vector.get("nonexistent_key"), std::out_of_range);
}


TEST(AllegroFlare_StableVectorStrTest, remove__will_remove_an_element)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "Element1");
   auto key2 = stable_vector.add("key2", "Element2");
   auto key3 = stable_vector.add("key3", "Element3");

   // Remove the middle element
   stable_vector.remove(key2);

   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_EQ(false, stable_vector.contains(key2));
   EXPECT_EQ(true, stable_vector.contains(key1));
   EXPECT_EQ(true, stable_vector.contains(key3));

   // Validate the remaining keys
   EXPECT_EQ(stable_vector.get(key1), "Element1");
   EXPECT_EQ(stable_vector.get(key3), "Element3");
}


TEST(AllegroFlare_StableVectorStrTest, remove__on_a_nonexistent_key__will_throw_an_error)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.add("key1", "Value1");
   EXPECT_THROW(stable_vector.remove("nonexistent_key"), std::out_of_range);
}


TEST(AllegroFlare_StableVectorStrTest, remove__when_only_the_one_element_exists__results_in_an_empty_container)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key = stable_vector.add("key1", "Value1");
   stable_vector.remove(key);
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_TRUE(stable_vector.empty());
   EXPECT_FALSE(stable_vector.contains(key));
}


TEST(AllegroFlare_StableVectorStrTest,
   remove__when_removing_the_last_element_that_was_added_when_multiple_elements_exist__will_work_as_expected)
{
   // Checks that it correctly removes the last element without disturbing others (tests the no-swap path in
   // the internal remove.

   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "First");
   auto key2 = stable_vector.add("key2", "Second");
   stable_vector.remove(key2);
   EXPECT_EQ(stable_vector.size(), 1);
   EXPECT_TRUE(stable_vector.contains(key1));
   EXPECT_FALSE(stable_vector.contains(key2));
   EXPECT_EQ(stable_vector.get(key1), "First");
}


TEST(AllegroFlare_StableVectorStrTest, get__when_the_container_is_empty__will_throw_an_error_on_a_missing_key)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_FALSE(stable_vector.contains("key1"));

   EXPECT_THROW(stable_vector.get("key1"), std::out_of_range);
}


TEST(AllegroFlare_StableVectorStrTest, retains_contiguous_data_under_modifications)
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


TEST(AllegroFlare_StableVectorStrTest, allocate__will_provide_an_allocated_block_for_that_key)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;

   // Add an uninitialized slot and modify it
   auto &value1 = stable_vector.allocate("key1");
   value1 = "Hello";

   // Verify the built value
   EXPECT_EQ(stable_vector.size(), 1);
   EXPECT_EQ(true, stable_vector.contains("key1"));
   EXPECT_EQ(stable_vector.get("key1"), "Hello");

   // Add another slot and modify it
   auto &value2 = stable_vector.allocate("key2");
   value2 = "World";

   // Verify the second value
   EXPECT_EQ(stable_vector.size(), 2);
   EXPECT_EQ(true, stable_vector.contains("key2"));
   EXPECT_EQ(stable_vector.get("key2"), "World");

   // Ensure the first value is still intact
   EXPECT_EQ(stable_vector.get("key1"), "Hello");
}


TEST(AllegroFlare_StableVectorStrTest, allocate__on_a_key_that_already_exists__will_throw_an_error)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.allocate("existing_key") = "Initial Value";
   EXPECT_THROW(stable_vector.allocate("existing_key"), std::invalid_argument);
}


TEST(AllegroFlare_StableVectorStrTest, emplace__will_add_elements_and_construct_them)
{
   struct ComplexType {
      std::string s;
      int i;
      ComplexType(std::string s, int i) : s(s), i(i) {}
   };

   AllegroFlare::StableVectorStr<ComplexType> stable_vector;
   stable_vector.emplace("item1", "test", 42);
   EXPECT_TRUE(stable_vector.contains("item1"));
   EXPECT_EQ(stable_vector.get("item1").s, "test");
   EXPECT_EQ(stable_vector.get("item1").i, 42);
}


TEST(AllegroFlare_StableVectorStrTest, emplace__on_a_key_that_already_exists__will_throw_an_error)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.emplace("duplicate_key", "Initial value constructed");
   EXPECT_THROW(stable_vector.emplace("duplicate_key", "Another value"), std::invalid_argument);
}


TEST(AllegroFlare_StableVectorStrTest, clear__on_a_populated_container__makes_it_empty)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   auto key1 = stable_vector.add("key1", "A");
   auto key2 = stable_vector.add("key2", "B");
   stable_vector.clear();
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_TRUE(stable_vector.empty());
   EXPECT_FALSE(stable_vector.contains(key1));
   EXPECT_FALSE(stable_vector.contains(key2));
}


TEST(AllegroFlare_StableVectorStrTest, clear__on_an_empty_container__has_no_effect_and_remains_empty)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.clear();
   EXPECT_EQ(stable_vector.size(), 0);
   EXPECT_TRUE(stable_vector.empty());
}


TEST(AllegroFlare_StableVectorStrTest, clear__then_adding_elements__works_correctly)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.add("key1", "A");
   stable_vector.clear();
   auto key2 = stable_vector.add("key2", "B");
   EXPECT_EQ(stable_vector.size(), 1);
   EXPECT_EQ(true, stable_vector.contains(key2));
   EXPECT_EQ(stable_vector.get(key2), "B");
}


TEST(AllegroFlare_StableVectorStrTest, empty__on_new_container__returns_true)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_EQ(true, stable_vector.empty());
}


TEST(AllegroFlare_StableVectorStrTest, empty__after_adding_element__returns_false)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.add("key1", "A");
   EXPECT_EQ(false, stable_vector.empty());
}


TEST(AllegroFlare_StableVectorStrTest, get_all_key_value_pairs__on_empty_container__returns_empty_vector)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   EXPECT_EQ(true, stable_vector.get_all_key_value_pairs().empty());
   
   const auto& const_stable_vector = stable_vector;
   EXPECT_EQ(true, const_stable_vector.get_all_key_value_pairs().empty());
}


TEST(AllegroFlare_StableVectorStrTest, get_all_key_value_pairs__returns_all_elements_correctly)
{
   AllegroFlare::StableVectorStr<std::string> stable_vector;
   stable_vector.add("keyA", "ValA");
   stable_vector.add("keyB", "ValB");
   
   auto pairs = stable_vector.get_all_key_value_pairs();
   EXPECT_EQ(pairs.size(), 2);
   
   bool foundA = false, foundB = false;
   for (const auto& p : pairs) {
      ASSERT_NE(p.first, nullptr);
      ASSERT_NE(p.second, nullptr);
      if (*p.first == "keyA" && *p.second == "ValA") foundA = true;
      if (*p.first == "keyB" && *p.second == "ValB") foundB = true;
   }
   EXPECT_EQ(true, foundA);
   EXPECT_EQ(true, foundB);

   // Test const version
   const auto& const_stable_vector = stable_vector;
   auto const_pairs = const_stable_vector.get_all_key_value_pairs();
   EXPECT_EQ(const_pairs.size(), 2);

   bool const_foundA = false, const_foundB = false;
   for (const auto& p : const_pairs) {
      ASSERT_NE(p.first, nullptr);
      ASSERT_NE(p.second, nullptr);
      if (*p.first == "keyA" && *p.second == "ValA") const_foundA = true;
      if (*p.first == "keyB" && *p.second == "ValB") const_foundB = true;
   }
   EXPECT_EQ(true, const_foundA);
   EXPECT_EQ(true, const_foundB);
}

