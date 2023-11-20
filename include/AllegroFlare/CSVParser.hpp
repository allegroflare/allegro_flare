#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class CSVParser
   {
   private:
      std::string csv_content;
      std::vector<std::vector<std::string>> parsed_content;

   protected:


   public:
      CSVParser();
      ~CSVParser();

      std::vector<std::string> parse_row(std::string line="[unset-line]");
   };
}



