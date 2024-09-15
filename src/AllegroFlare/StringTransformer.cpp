

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
      error_message << "[AllegroFlare::StringTransformer::expand]: error: guard \"(num_spaces >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StringTransformer::expand]: error: guard \"(num_spaces >= 0)\" not met");
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

std::string StringTransformer::join_quoted_with_commas(std::set<std::string>* elements)
{
   if (!(elements))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StringTransformer::join_quoted_with_commas]: error: guard \"elements\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StringTransformer::join_quoted_with_commas]: error: guard \"elements\" not met");
   }
   std::ostringstream result;
   for (auto it = elements->begin(); it != elements->end(); ++it)
   {
       if (it != elements->begin()) result << ", ";
       result << quote_and_escape_inner_quotes(*it);
   }
   return result.str();
}

std::string StringTransformer::join_with_commas(std::set<std::string>* elements)
{
   if (!(elements))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StringTransformer::join_with_commas]: error: guard \"elements\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StringTransformer::join_with_commas]: error: guard \"elements\" not met");
   }
   std::ostringstream result;
   for (auto it = elements->begin(); it != elements->end(); ++it)
   {
       if (it != elements->begin()) result << ", ";
       result << *it;
   }
   return result.str();
}

std::string StringTransformer::join(std::vector<std::string>* elements, std::string interpolation_string)
{
   if (!(elements))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::StringTransformer::join]: error: guard \"elements\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::StringTransformer::join]: error: guard \"elements\" not met");
   }
   std::ostringstream result;
   for (auto it = elements->begin(); it != elements->end(); ++it)
   {
       if (it != elements->begin()) result << interpolation_string;
       result << *it;
   }
   return result.str();
}

std::string StringTransformer::remove_non_alphanumeric(std::string input)
{
   std::string output = "";
   for (std::size_t i=0; i<input.size(); i++)
   {
       if (isalnum(input[i])) output += input[i];
       //|| isspace(input[i]))
       //{
           //output += input[i];
       //}
   }
   return output;
}

std::string StringTransformer::quote_and_escape_inner_quotes(std::string subject)
{
   // TODO: Test this
   return "\"" + replace(subject, "\"", "\\\"") + "\"";
}

std::string StringTransformer::replace(std::string subject, std::string search, std::string replace)
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

std::vector<std::string> StringTransformer::split(std::string string, char delimiter)
{
   std::vector<std::string> elems;
   auto result = std::back_inserter(elems);
   std::stringstream ss(string);
   std::string item;
   while (std::getline(ss, item, delimiter)) { *(result++) = item; }
   return elems;
}

std::vector<std::string> StringTransformer::tokenize(std::string str, char delim)
{
   std::vector<std::string> tokens = split(str, delim);
   for (auto &token : tokens) token = trim(token);
   return tokens;
}

std::string StringTransformer::trim(std::string s)
{
   // ltrim
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
   // rtrim
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   return s;
}


} // namespace AllegroFlare


