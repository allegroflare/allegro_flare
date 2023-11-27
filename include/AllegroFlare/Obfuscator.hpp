#pragma once


#include <AllegroFlare/Obfuscators/Rotate.hpp>
#include <string>


namespace AllegroFlare
{
   class Obfuscator
   {
   private:
      AllegroFlare::Obfuscators::Rotate rotator_engine;

   protected:


   public:
      Obfuscator();
      ~Obfuscator();

      std::string encode(std::string text="[unset-text]");
      std::string decode(std::string text="[unset-text]");
   };
}



