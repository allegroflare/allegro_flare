#pragma once


#include <string>


namespace AllegroFlare
{
   class Obfuscator
   {
   private:

   protected:


   public:
      Obfuscator();
      ~Obfuscator();

      std::string encode(std::string text="[unset-text]");
   };
}



