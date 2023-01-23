#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class Logger
   {
   private:
      static std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");
      static std::string quote_and_escape_inner_quotes(std::string subject="[unset-subject]");
      static std::string replace(std::string subject="[unset-subject]", std::string search="[unset-search]", std::string replace="[unset-replace]");

   protected:


   public:
      Logger();
      ~Logger();

      static std::string build_error_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_guard_error_message(std::string from="[unset-from]", std::string guard_statement="[unset-guard_statement]");
      static std::string build_warning_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_not_included_message(std::string element_not_present="[unset-missing_element]", std::vector<std::string> valid_elements={});
      static std::string build_unhandled_case_message(std::string unhandled_case="[unset-unhandled_case]");
      static std::string build_info_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_missing_file_error(std::string from="[unset-from]", std::string filename="[unset-filename]", std::string filetype="[unset-filetype]");
      static void info_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void warn_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_error(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_unhandled_case(std::string from="[unset-from]", std::string unhandled_case="[unset-unhandled_case]");
   };
}



