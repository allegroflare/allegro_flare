
#include <gtest/gtest.h>

#include <AllegroFlare/YAMLValidator.hpp>


TEST(AllegroFlare_YAMLValidatorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::YAMLValidator yaml_cpp_validator;
}


TEST(AllegroFlare_YAMLValidatorTest, validate_elements_are_unique__will_return_true_on_an_empty_vector)
{
   std::vector<std::string> empty_vector;
   EXPECT_EQ(true, AllegroFlare::YAMLValidator::validate_elements_are_unique(empty_vector));
}


TEST(AllegroFlare_YAMLValidatorTest, validate_elements_are_unique__with_a_vector_with_unique_elements__will_return_true)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "date"};
   EXPECT_EQ(true, AllegroFlare::YAMLValidator::validate_elements_are_unique(vector));
}


TEST(AllegroFlare_YAMLValidatorTest,
   validate_elements_are_unique__with_a_vector_that_does_not_contain_unique_elements__will_return_false)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "banana"};
   EXPECT_EQ(false, AllegroFlare::YAMLValidator::validate_elements_are_unique(vector));
}


TEST(AllegroFlare_YAMLValidatorTest,
   validate_node_has_unsigned_int_value__will_return_true_if_the_node_contains_a_positive_integer)
{
   std::vector<std::string> test_data = { "1234", "1", "999999", "0" };
   // TODO: Test on other datatypes (float, bool, etc)

   for (auto &test_data_item : test_data)
   {
      YAML::Node node;
      node["key"] = test_data_item;
      EXPECT_EQ(true, AllegroFlare::YAMLValidator::validate_node_has_unsigned_int_value(node, "key"));
   }
}


TEST(AllegroFlare_YAMLValidatorTest,
   validate_node_has_unsigned_int_value__will_return_false_if_the_node_does_not_contain_an_unsigned_integer)
{
   std::vector<std::string> test_data = { "-1234", "-1", "-999999", "012", "-0", "&abier", " wohoasd", " ", "    \n" };
   // TODO: Test on other datatypes (float, bool, etc)

   for (auto &test_data_item : test_data)
   {
      YAML::Node node;
      node["key"] = test_data_item;
      EXPECT_EQ(false, AllegroFlare::YAMLValidator::validate_node_has_unsigned_int_value(node, "key"));
   }
}


TEST(AllegroFlare_YAMLValidatorTest, validate_node_is_one_of_type__if_node_is_valid__will_return_true)
{
   // TODO
}


TEST(AllegroFlare_YAMLValidatorTest,
   validate_node_is_one_of_type__if_node_type_is_not_in_the_list__will_throw_an_error)
{
   // TODO
}


