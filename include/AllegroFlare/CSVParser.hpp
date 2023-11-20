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
      std::string raw_csv_content;
      std::vector<std::vector<std::string>> parsed_content;
      bool parsed;

   protected:


   public:
      CSVParser(std::string raw_csv_content="[unset-csv_content]");
      ~CSVParser();

      bool get_parsed() const;
      void set_raw_csv_content(std::string raw_csv_content="[unset-raw_csv_content]");
      std::vector<std::vector<std::string>> get_parsed_content();
      void parse();
      std::vector<std::string> parse_row(std::string line="[unset-line]");
   };
}



