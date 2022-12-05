

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
   return (string.length() <= max);
}

bool StringFormatValidator::only_numerical_characters()
{
   return (string.find_first_not_of("9876543210") == std::string::npos);
}


} // namespace AllegroFlare


