

#include <AllegroFlare/Obfuscators/Rotate.hpp>

#include <set>


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


void Rotate::set_rotation(std::size_t rotation)
{
   this->rotation = rotation;
}


std::size_t Rotate::get_rotation() const
{
   return rotation;
}


std::string Rotate::encode(std::string text)
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

std::string Rotate::decode(std::string text)
{
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


