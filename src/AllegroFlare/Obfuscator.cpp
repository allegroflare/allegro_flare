

#include <AllegroFlare/Obfuscator.hpp>

#include <set>


namespace AllegroFlare
{


Obfuscator::Obfuscator()
   : rotation_set(" \n\r\tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}1234567890!@#$%^&*()_+-=,./<>?:;\"\\~")
{
}


Obfuscator::~Obfuscator()
{
}


std::string Obfuscator::encode(std::string text)
{
   //std::string rotation_set =
      //" \n\r\tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}1234567890!@#$%^&*()_+-=,./<>?:;\"'\\~";
   //std::set<char> chars;
   //for (auto &c : rotation_set) chars.insert(c);

   std::string result;

   // Rotate
   //char c = 'a';
   for (auto &c : text)
   {
      int rotation = 4;
      std::size_t pos;
      if ((pos=rotation_set.find(c))==std::string::npos)
      {
         result += c;
      }
      else
      {
         result += rotation_set[(pos+rotation) % rotation_set.size()];
      }
   }

   // TODO: Map chars to their encodings

   return result;
}


} // namespace AllegroFlare


