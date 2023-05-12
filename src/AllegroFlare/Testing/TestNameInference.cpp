

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
   // Concede that this is relative and does assume that the folder exists.  In the future, these result
   // snapshots should be stored in a specific folder for *each build*.  This will accumulate over time, so might
   // need to be cleaned occasionally.  This should also detect if there is a png file with the name already
   // present, and appnd a (2) after it.
   return "./tmp/test_snapshots/" + build_full_test_name_str() + ".png";
}

bool TestNameInference::is_valid_prefix_token(std::string possible_prefix_token)
{
   if (possible_prefix_token.empty() || !isupper(possible_prefix_token[0]))
   {
      return false;
   }
   bool prev_is_underscore = false;
   for (char c : possible_prefix_token)
   {
      if (!isalnum(c) && c != '_')
      {
         return false;
      }
      if (c == '_' && prev_is_underscore)
      {
         return false;
      }
      prev_is_underscore = (c == '_');
   }
   return true;
}

std::vector<std::string> TestNameInference::split(std::string input, std::string delimiter)
{
   std::vector<std::string> tokens;
   size_t start = 0, end = 0;
   while ((end = input.find(delimiter, start)) != std::string::npos)
   {
      tokens.push_back(input.substr(start, end - start));
      start = end + delimiter.length();
   }
   tokens.push_back(input.substr(start));
   return tokens;
}


} // namespace Testing
} // namespace AllegroFlare


