#pragma once


#include <string>


namespace AllegroFlare
{
   class Logger
   {
   private:

   protected:


   public:
      Logger();
      ~Logger();

      static std::string build_error_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_warning_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static std::string build_info_message(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_missing_file_error(std::string from="[unset-from]", std::string filename="[unset-filename]", std::string filetype="[unset-filetype]");
      static void warn_from(std::string from="[unset-from]", std::string message="[unset-message]");
      static void throw_error(std::string from="[unset-from]", std::string message="[unset-message]");
   };
}



