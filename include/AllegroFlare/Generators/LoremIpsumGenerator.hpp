#pragma once


#include <string>
#include <vector>


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
         void generate_characters(int num_characters=1);
         void generate_characters_about(int num_characters=1);
         void generate_words(int num_words=1);
         std::string generate_sentences(int num_sentences=1);
         std::string generate_paragraphs(int num_paragraphs=1);
         static std::string generate_source_text();
         std::vector<std::string> split(std::string text="", char delimiter=' ');
         std::string join(std::vector<std::string> tokens={}, std::string delimiter=", ");
      };
   }
}



