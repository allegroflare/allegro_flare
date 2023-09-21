#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Testing
   {
      class TestNameInference
      {
      private:

      protected:


      public:
         TestNameInference();
         ~TestNameInference();

         static std::string get_test_name();
         static std::string get_test_suite_name();
         static std::string build_full_test_name_str();
         static std::string build_test_snapshot_full_filename();
         static std::vector<std::string> extract_prefix_tokens(std::string str="[unset-str]");
         static bool is_valid_prefix_token_format(std::string possible_prefix_token="[unset-possible_prefix_token]");
         static std::vector<std::string> split(std::string input="[unset-input]", std::string delimiter="__");
      };
   }
}



