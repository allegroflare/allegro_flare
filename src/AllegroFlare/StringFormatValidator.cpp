

#include <AllegroFlare/StringFormatValidator.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


StringFormatValidator::StringFormatValidator(std::string string)
   : string(string)
{
}


StringFormatValidator::~StringFormatValidator()
{
}


void StringFormatValidator::set_string(std::string string)
{
   this->string = string;
}


std::string StringFormatValidator::get_string() const
{
   return string;
}


bool StringFormatValidator::fits_max_length(std::size_t max)
{
   return (string.size() <= max);
}

bool StringFormatValidator::fits_min_length(std::size_t min)
{
   return (string.size() >= min);
}

bool StringFormatValidator::has_only_numerical_characters()
{
   return (string.find_first_not_of("9876543210") == std::string::npos);
}

bool StringFormatValidator::ends_with(std::string ending)
{
   if (string.length() >= ending.length())
   {
      return string.compare(string.length() - ending.length(), ending.length(), ending) == 0;
   }
   return false;
}

bool StringFormatValidator::is_uppercase_symbol_name()
{
   bool at_first_char = true; // Flag to track the first character

   if (string.empty()) return false;

   for (char c : string) {
      if (at_first_char && !(std::isupper(c) || c == '_'))
      {
          return false; // First character must be uppercase
      }
      else if (!std::isalnum(c) && c != '_')
      {
          return false; // Characters must be uppercase, numbers, or underscores
      }

      at_first_char = false; // Set the flag to false after the first character
   }
   return true;
}

bool StringFormatValidator::is_blank()
{
   // TODO: Test this function
   return string.empty();
}

bool StringFormatValidator::matches(std::string other)
{
   return string == other;
}

bool StringFormatValidator::contains_none(std::vector<std::string> strings_to_match)
{
   if (!((!strings_to_match.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StringFormatValidator::contains_none]: error: guard \"(!strings_to_match.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StringFormatValidator::contains_none]: error: guard \"(!strings_to_match.empty())\" not met");
   }
   for (const std::string& str : strings_to_match)
   {
      if (string.find(str) != std::string::npos) {
         return false;
      }
   }
   return true;
}


} // namespace AllegroFlare


