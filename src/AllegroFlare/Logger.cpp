

#include <AllegroFlare/Logger.hpp>

#include <AllegroFlare/ConsoleColors.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>


namespace AllegroFlare
{


Logger::Logger()
{
}


Logger::~Logger()
{
}


std::string Logger::build_error_message(std::string from, std::string message)
{
   //const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   //const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   std::stringstream result;
   result << CONSOLE_COLOR_RED << "[" << from << "]: error: " << message << CONSOLE_COLOR_DEFAULT << std::endl;
   return result.str();
}

std::string Logger::build_warning_message(std::string from, std::string message)
{
   //const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   //const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   std::stringstream result;
   result << CONSOLE_COLOR_YELLOW << "[" << from << "]: warning: " << message << CONSOLE_COLOR_DEFAULT;
   return result.str();
}

std::string Logger::build_not_included_message(std::string element_not_present, std::vector<std::string> valid_elements)
{
   std::stringstream result;
   result << "The element "
          << quote_and_escape_inner_quotes(element_not_present)
          << " is not in the list of valid elements [";
   for (auto &valid_element : valid_elements)
   {
      valid_element = quote_and_escape_inner_quotes(valid_element);
   }
   result << join(valid_elements, ", ");
   result << "]";
   return result.str();
}

std::string Logger::build_unhandled_case_message(std::string unhandled_case)
{
   std::stringstream result;
   result << "Unhandled case for case " << quote_and_escape_inner_quotes(unhandled_case) << ".";
   return result.str();
}

std::string Logger::build_info_message(std::string from, std::string message)
{
   //const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   //const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   std::stringstream result;
   result << CONSOLE_COLOR_CYAN << "[" << from << "]: info: " << message << CONSOLE_COLOR_DEFAULT << std::endl;
   return result.str();
}

void Logger::throw_missing_file_error(std::string from, std::string filename, std::string filetype)
{
   std::stringstream error_message;
   std::string current_path = std::filesystem::current_path().string();

   error_message << "The expected " << filetype << " file does not exist. "
                 << "Looking for \"" << filename << "\" from the current path "
                 << "\"" << current_path << "\".";
   throw_error(from, error_message.str());
   return;
}

void Logger::warn_from(std::string from, std::string message)
{
   std::cout << build_warning_message(from, message) << std::endl;
}

void Logger::throw_error(std::string from, std::string message)
{
   std::stringstream error_message;
   error_message << "[" << from << "]: error: " << message;

   //const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   //const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();

   throw std::runtime_error(error_message.str());
}

void Logger::throw_unhandled_case(std::string from, std::string unhandled_case)
{
   std::stringstream error_message;
   std::string message = build_unhandled_case_message(unhandled_case);
   error_message << "[" << from << "]: error: " << message;

   std::stringstream error_message_for_cout;
   error_message_for_cout << CONSOLE_COLOR_RED
                          << "[" << from << "] error: " << message
                          << CONSOLE_COLOR_DEFAULT << std::endl;

   std::cout << error_message_for_cout.str();

   throw std::runtime_error(error_message.str());
}

std::string Logger::join(std::vector<std::string> tokens, std::string delimiter)
{
   std::stringstream result;
   bool last = false;

   for (unsigned i=0; i<tokens.size(); i++)
   {
      result << tokens[i];
      if (i == tokens.size()-1) last = true;
      if (!last) result << delimiter;
   }

   return result.str();
}

std::string Logger::quote_and_escape_inner_quotes(std::string subject)
{
   return "\"" + replace(subject, "\"", "\\\"") + "\"";
}

std::string Logger::replace(std::string subject, std::string search, std::string replace)
{
   std::string buffer;

   int sealeng = search.length();
   int strleng = subject.length();

   if (sealeng==0)
      return subject;//no change

   for(int i=0, j=0; i<strleng; j=0 )
   {
      while (i+j<strleng && j<sealeng && subject[i+j]==search[j])
         j++;
      if (j==sealeng)//found 'search'
      {
         buffer.append(replace);
         i+=sealeng;
      }
      else
      {
         buffer.append( &subject[i++], 1);
      }
   }
   subject = buffer;
   return subject;
}


} // namespace AllegroFlare


