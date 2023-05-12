
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/TestNameInference.hpp>


TEST(AllegroFlare_Testing_TestNameInferenceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
}


TEST(AllegroFlare_Testing_TestNameInferenceTest, get_test_name__returns_the_name_of_the_test)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
   std::string expected_test_name = "get_test_name__returns_the_name_of_the_test";
   std::string actual_test_name = test_name_inference.get_test_name();
   EXPECT_EQ(expected_test_name, actual_test_name);
}


TEST(AllegroFlare_Testing_TestNameInferenceTest, get_test_suite_name__returns_the_name_of_the_test_suite)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
   std::string expected_test_suite_name = "AllegroFlare_Testing_TestNameInferenceTest";
   std::string actual_test_suite_name = test_name_inference.get_test_suite_name();
   EXPECT_EQ(expected_test_suite_name, actual_test_suite_name);
}


TEST(AllegroFlare_Testing_TestNameInferenceTest, build_full_test_name_str__returns_a_full_decorated_name_of_the_test)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
   std::string expected_full_test_name = "AllegroFlare_Testing_TestNameInferenceTest - build_full_test_name_str__"
                                         "returns_a_full_decorated_name_of_the_test";
   std::string actual_full_test_name = test_name_inference.build_full_test_name_str();
   EXPECT_EQ(expected_full_test_name, actual_full_test_name);
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   build_test_snapshot_full_filename__returns_a_relative_png_filename_for_the_test_snapshot)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
   std::string expected_snapshot_filename = "./tmp/test_snapshots/AllegroFlare_Testing_TestNameInferenceTest - build_"
                                            "test_snapshot_full_filename__returns_a_relative_png_filename_for_the_test_"
                                            "snapshot.png";
   std::string actual_snapshot_filename = test_name_inference.build_test_snapshot_full_filename();
   EXPECT_EQ(expected_snapshot_filename, actual_snapshot_filename);
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   is_valid_prefix_token__will_return_true_on_valid_tokens)
{
   std::vector<std::string> valid_prefix_tokens = {"TOKEN", "TOKEN2", "ANOTHER_TOKEN"};

   for (int i = 0; i < valid_prefix_tokens.size(); ++i)
   {
      EXPECT_EQ(true, AllegroFlare::Testing::TestNameInference::is_valid_prefix_token(valid_prefix_tokens[i]));
   }
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   is_valid_prefix_token__will_return_false_on_invalid_tokens)
{
   std::vector<std::string> invalid_prefix_tokens = {
      "some_words", "another_word", "__", "_", "  ", "", "1234", "1ABA", "SOME__TOKEN"
   };
   for (int i = 0; i < invalid_prefix_tokens.size(); ++i)
   {
      EXPECT_EQ(false, AllegroFlare::Testing::TestNameInference::is_valid_prefix_token(invalid_prefix_tokens[i]));
   }
}


TEST(AllegroFlare_Testing_TestNameInferenceTest, split__will_split_the_string_by_the_delimiter)
{
   std::string input = "token tooken talkin talk";
   std::vector<std::string> expected_output = { "token", "tooken", "talkin", "talk" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::split(input, " "));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   split__will_split_the_string_with_a_delimiter_that_is_more_than_one_character)
{
   std::string input = "FOO__BAR__BAZ_BIZ__this_is_a_test";
   std::vector<std::string> expected_output = { "FOO", "BAR", "BAZ_BIZ", "this_is_a_test" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::split(input, "__"));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   ValidInput)
{
   std::string input = "TOKEN__TOKEN2__ANOTHER_TOKEN__some_words__another_word";
   std::vector<std::string> expected_output = { "TOKEN", "TOKEN2", "ANOTHER_TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   InvalidInput)
{
   std::string input = "TOKEN__ANOTHER_TOKEN__some_words__another_word";
   std::vector<std::string> expected_output = { "TOKEN", "ANOTHER_TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   extract_prefix_tokens__will_not_include_empty_tokens)
{
   std::string input = "TOKEN____ANOTHER_TOKEN";
   std::vector<std::string> expected_output = { "TOKEN", "ANOTHER_TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   extract_prefix_tokens__will_not_include_valid_format_tokens_that_occur_after_non_token_text)
{
   std::string input =
      "TOKEN__12345__ANOTHER_TOKEN__some_words__another_word__ANOTHER_ALLCAPS_TOKEN_THAT_SHOULD_BE_IGNORED";
   std::vector<std::string> expected_output = { "TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   SingleToken)
{
   std::string input = "TOKEN";
   std::vector<std::string> expected_output = { "TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   NoTokens)
{
   std::string input = "some_words__another_word";
   std::vector<std::string> expected_output = {};
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   EmptyInput)
{
   std::string input = "";
   std::vector<std::string> expected_output = {};
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   TokenWithUnderscoreAtEnd)
{
   std::string input = "TOKEN_";
   std::vector<std::string> expected_output = { "TOKEN_" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


TEST(AllegroFlare_Testing_TestNameInferenceTest,
   TokenWithdoubleUnderscoreAtEnd)
{
   std::string input = "TOKEN__";
   std::vector<std::string> expected_output = { "TOKEN" };
   EXPECT_EQ(expected_output, AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(input));
}


