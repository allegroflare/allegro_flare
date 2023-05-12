#pragma once


#include <string>


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
         static bool is_valid_prefix_token(std::string possible_prefix_token="[unset-possible_prefix_token]");
      };
   }
}



