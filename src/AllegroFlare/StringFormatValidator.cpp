

#include <AllegroFlare/StringFormatValidator.hpp>




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


} // namespace AllegroFlare


