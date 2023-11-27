

#include <AllegroFlare/Obfuscator.hpp>

#include <set>


namespace AllegroFlare
{


Obfuscator::Obfuscator()
{
}


Obfuscator::~Obfuscator()
{
}


std::string Obfuscator::encode(std::string text)
{
   std::string rotation_set =
      " \n\r\tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}1234567890!@#$%^&*()_+-=,./<>?:;\"'\\~";
   std::set<char> chars;
   for (auto &c : rotation_set) chars.insert(c);

   // TODO: Map chars to their encodings

   return text;
}


} // namespace AllegroFlare


