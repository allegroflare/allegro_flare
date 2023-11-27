

#include <AllegroFlare/Obfuscator.hpp>

#include <set>


namespace AllegroFlare
{


Obfuscator::Obfuscator()
   : rotation_set(" \n\r\tabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ[]{}1234567890!@#$%^&*()_+-=,./<>?:;\"\\~")
   , rotation(4)
{
}


Obfuscator::~Obfuscator()
{
}


void Obfuscator::set_rotation(std::size_t rotation)
{
   this->rotation = rotation;
}


std::size_t Obfuscator::get_rotation() const
{
   return rotation;
}


std::string Obfuscator::encode(std::string text)
{
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

std::string Obfuscator::decode(std::string text)
{
   std::string result;

   // Rotate
   //char c = 'a';
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
         result += rotation_set[(pos-rotation) % rotation_set.size()];
      }
   }

   // TODO: Map chars to their encodings

   return result;
}


} // namespace AllegroFlare


