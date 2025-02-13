#pragma once


#include <AllegroFlare/ClassAndMethodNameInference.hpp>
#include <AllegroFlare/Instrumentation/PrimaryProcessEventMetric.hpp>
#include <AllegroFlare/Logger.hpp>
#include <fstream>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class Logger
   {
   public:
      static constexpr char* DEFAULT_INSTRUMENTATION_LOG_FILENAME = (char*)"instrumentation.log";
      static constexpr char* DEFAULT_LOG_FILENAME = (char*)"allegro_flare.log";

   private:
      static std::set<std::string> once_emitted_warnings;
      static std::string log_filename;
      static std::ofstream log_file;
      static bool log_file_initialized;
      static std::string instrumentation_log_filename;
      static std::ofstream instrumentation_log_file;
      static bool instrumentation_log_file_initialized;
      static AllegroFlare::Logger* instance;
      static std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");
      static std::string quote_and_escape_inner_quotes(std::string subject="[unset-subject]");
      static std::string replace(std::string subject="[unset-subject]", std::string search="[unset-search]", std::string replace="[unset-replace]");

   protected:


   public:
      Logger();
      ~Logger();

      void __dummy_dependency_trigger(int foo=0);
      static void set_instance(AllegroFlare::Logger* instance_to_use=nullptr);
      static void clear_instance();
      static bool has_instance();
      void set_log_filename(std::string log_filename=DEFAULT_LOG_FILENAME);
      void initialize_log_file();
      void close_log_file();
      void set_instrumentation_log_filename(std::string instrumentation_log_filename=DEFAULT_INSTRUMENTATION_LOG_FILENAME);
      void initialize_instrumentation_log_file();
      void close_instrumentation_log_file();
      static void outstream_instrumentation_metric(AllegroFlare::Instrumentation::PrimaryProcessEventMetric* metric=nullptr);
      static std::string build_error_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_warning_message(std::string from="[unset-from]", std::string message="[unset-message]", bool is_warn_once=false);
      static std::string build_guard_error_message(std::string from="[unset-from]", std::string guard_statement="[unset-guard_statement]");
      static std::string build_not_included_message(std::string element_not_present="[unset-missing_element]", std::vector<std::string> valid_elements={});
      static std::string build_unimplemented_for_base_class_message(std::string from="[unset-from]");
      static std::string build_info_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_unhandled_case_message(std::string unhandled_case="[unset-unhandled_case]");
      static void throw_missing_file_error(std::string from="[unset-from]", std::string filename="[unset-filename]", std::string filetype="[unset-filetype]");
      static void throw_unimplemented_for_base_class_error(std::string from="[unset-from]");
      static void info_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void warn_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void warn_from_once(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_error(std::string from="[unset-from]", std::string message="[unset-message]");
      static void error_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_unhandled_case(std::string from="[unset-from]", std::string unhandled_case="[unset-unhandled_case]");
   };
}



