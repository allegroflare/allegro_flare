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
         std::string generate_words(int num_words=1);
         std::string generate_paragraphs(int num_paragraphs=1);
         std::string generate_characters(int num_characters=1);
         static std::string generate_source_text();
      };
   }
}



