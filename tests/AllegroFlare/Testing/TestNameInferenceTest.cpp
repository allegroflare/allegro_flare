
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


