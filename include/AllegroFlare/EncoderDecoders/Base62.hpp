#pragma once


#include <cstddef>
#include <string>


namespace AllegroFlare
{
   namespace EncoderDecoders
   {
      class Base62
      {
      private:
         static std::string CHARACTERS_LOWERCASE_FIRST;

      protected:


      public:
         Base62();
         ~Base62();

         std::string encode(int value=0, std::size_t zerofill_count=0);
         int decode(std::string value="0");
      };
   }
}



