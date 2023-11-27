#pragma once


#include <string>


namespace AllegroFlare
{
   class Obfuscator
   {
   private:
      std::string rotation_set;

   protected:


   public:
      Obfuscator();
      ~Obfuscator();

      std::string encode(std::string text="[unset-text]");
   };
}



