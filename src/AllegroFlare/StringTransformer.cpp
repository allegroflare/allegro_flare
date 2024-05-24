

#include <AllegroFlare/StringTransformer.hpp>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


StringTransformer::StringTransformer(std::string text)
   : text(text)
{
}


StringTransformer::~StringTransformer()
{
}


std::string StringTransformer::get_text() const
{
   return text;
}


AllegroFlare::StringTransformer& StringTransformer::upcase()
{
   //std::string result = original_text;
   // note: the 4th argument casts std::toupper with a specific signature.  This is to prevent
   // a compile error on Windows that is unable to resolve which "std::toupper" function to use
   // see https://stackoverflow.com/a/16792532
   std::transform(
      text.begin(),
      text.end(),
      text.begin(),
      static_cast<int(*)(int)>(std::toupper)
   );

   return *this;
}

AllegroFlare::StringTransformer& StringTransformer::expand(int num_spaces)
{
   if (!((num_spaces >= 0)))
   {
      std::stringstream error_message;
      error_message << "[StringTransformer::expand]: error: guard \"(num_spaces >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("StringTransformer::expand: error: guard \"(num_spaces >= 0)\" not met");
   }
   std::string interpolate_string(num_spaces, ' ');
   std::stringstream result;

   for (size_t i=0; i<text.size(); i++)
   {
      result << text[i];

      // Append interpolate_string if not at the last character
      if (i != text.size() - 1) {
          result << interpolate_string;
      }
   }

   text = result.str();

   return *this;
}

std::string StringTransformer::join_with_commas(std::set<std::string>* elements)
{
   if (!(elements))
   {
      std::stringstream error_message;
      error_message << "[StringTransformer::join_with_commas]: error: guard \"elements\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("StringTransformer::join_with_commas: error: guard \"elements\" not met");
   }
   std::ostringstream result;
   for (auto it = elements->begin(); it != elements->end(); ++it)
   {
       if (it != elements->begin()) result << ", ";
       result << *it;
   }
   return result.str();
}


} // namespace AllegroFlare


