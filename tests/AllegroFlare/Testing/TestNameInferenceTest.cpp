
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/TestNameInference.hpp>


TEST(AllegroFlare_Testing_TestNameInferenceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Testing::TestNameInference test_name_inference;
}


// TODO: test get_test_name
// TODO: test get_test_suite_name
// TODO: test build_full_test_name_str
// TODO: build_test_snapshot_full_filename


