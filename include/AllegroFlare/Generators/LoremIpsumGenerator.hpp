#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Generators
   {
      class LoremIpsumGenerator
      {
      private:
         std::string source_text;

      public:
         LoremIpsumGenerator();
         ~LoremIpsumGenerator();

         std::string get_source_text();
         static std::string generate_source_text();
      };
   }
}



