

#include <AllegroFlare/Testing/TestNameInference.hpp>

#include <gtest/gtest.h>


namespace AllegroFlare
{
namespace Testing
{


TestNameInference::TestNameInference()
{
}


TestNameInference::~TestNameInference()
{
}


std::string TestNameInference::get_test_name()
{
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->name();
}

std::string TestNameInference::get_test_suite_name()
{
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->test_suite_name();
}

std::string TestNameInference::build_full_test_name_str()
{
   return get_test_suite_name() + " - " + get_test_name();
}

std::string TestNameInference::build_test_snapshot_full_filename()
{
   // TODO: improve this logic dependent on #define and not in sync with Testing/WithAllegroRenderingFixture
   #ifdef _WIN32
   #define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
   #else
   #define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
   #endif
   return TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER + build_full_test_name_str() + ".png";
}


} // namespace Testing
} // namespace AllegroFlare


