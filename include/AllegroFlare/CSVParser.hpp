#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class CSVParser
   {
   private:
      enum class ParseState
      {
         NORMAL = 0,
         INSIDE_QUOTES,
      };
      std::string csv_content;
      std::vector<std::vector<std::string>> parsed_content;

   protected:


   public:
      CSVParser();
      ~CSVParser();

      std::vector<std::string> parse_row(std::string line="[unset-line]");
   };
}



