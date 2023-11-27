

#include <AllegroFlare/Obfuscators/Rotate.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Obfuscators
{


Rotate::Rotate()
   : rotation_set(" \n\r\tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}1234567890!@#$%^&*()_+-=,./<>?:;\"\\~")
   , rotation(4)
{
}


Rotate::~Rotate()
{
}


void Rotate::set_rotation_set(std::string rotation_set)
{
   this->rotation_set = rotation_set;
}


void Rotate::set_rotation(std::size_t rotation)
{
   this->rotation = rotation;
}


std::string Rotate::get_rotation_set() const
{
   return rotation_set;
}


std::size_t Rotate::get_rotation() const
{
   return rotation;
}


bool Rotate::rotation_set_contains_unique_characters()
{
   std::set<char> uniq_chars;
   for (auto &c : rotation_set) uniq_chars.insert(c);
   return (uniq_chars.size() == rotation_set.size());
}

std::string Rotate::encode(std::string text)
{
   if (!(rotation_set_contains_unique_characters()))
   {
      std::stringstream error_message;
      error_message << "[Rotate::encode]: error: guard \"rotation_set_contains_unique_characters()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rotate::encode: error: guard \"rotation_set_contains_unique_characters()\" not met");
   }
   std::string result;

   // Rotate
   //char c = 'a';
   for (auto &c : text)
   {
      //int rotation = 4;
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

std::string Rotate::decode(std::string text)
{
   if (!(rotation_set_contains_unique_characters()))
   {
      std::stringstream error_message;
      error_message << "[Rotate::decode]: error: guard \"rotation_set_contains_unique_characters()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Rotate::decode: error: guard \"rotation_set_contains_unique_characters()\" not met");
   }
   std::string result;

   // Rotate
   //char c = 'a';
   int rev_rotation_i = -((int)rotation);
   while (rev_rotation_i < 0) rev_rotation_i += rotation_set.size();
   std::size_t rev_rotation = (std::size_t)(rev_rotation_i);

   for (auto &c : text)
   {
      //int rotation = -4;
      std::size_t pos;
      if ((pos=rotation_set.find(c))==std::string::npos)
      {
         result += c;
      }
      else
      {
         result += rotation_set[(pos+rev_rotation) % rotation_set.size()];
      }
   }

   // TODO: Map chars to their encodings

   return result;
}


} // namespace Obfuscators
} // namespace AllegroFlare


