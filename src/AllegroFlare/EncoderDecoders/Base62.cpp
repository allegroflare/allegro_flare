

#include <AllegroFlare/EncoderDecoders/Base62.hpp>



namespace AllegroFlare
{
namespace EncoderDecoders
{


std::string Base62::CHARACTERS_LOWERCASE_FIRST = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


Base62::Base62()
{
}


Base62::~Base62()
{
}


std::string Base62::encode(int value)
{
   std::string str;

   do
   {
      str.insert(0, std::string(1, CHARACTERS_LOWERCASE_FIRST[value % 62]));
      value /= 62;
   }
   while (value > 0);

   return str;
}

int Base62::decode(std::string value)
{
   std::reverse(value.begin(), value.end());

   int ret = 0;
   int count = 1;
   for (char& character : value)
   {
      ret += CHARACTERS_LOWERCASE_FIRST.find(character) * count;
      count *= 62;
   }

   return ret;
}
} // namespace EncoderDecoders
} // namespace AllegroFlare


