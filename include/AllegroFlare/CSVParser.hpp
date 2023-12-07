#pragma once


#include <map>
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
      int num_header_rows;
      std::map<std::string, int> column_headers;
      bool loaded;
      bool column_headers_assembled;
      bool parsed;

   protected:


   public:
      CSVParser(std::string raw_csv_content="[unset-csv_content]");
      ~CSVParser();

      std::map<std::string, int> get_column_headers() const;
      bool get_column_headers_assembled() const;
      bool get_parsed() const;
      void set_raw_csv_content(std::string raw_csv_content="[unset-raw_csv_content]");
      int num_raw_rows();
      int num_rows();
      int num_records();
      int num_columns();
      std::vector<std::vector<std::string>> get_parsed_content();
      void parse();
      std::vector<std::string> parse_row(std::string line="[unset-line]");
      int get_num_header_rows();
      int get_column_header_column_num_or_throw(std::string column_header_name="[unset-column_header_name]");
      bool column_header_exists(std::string column_header_name="[unset-column_header_name]");
      std::vector<std::map<std::string, std::string>> extract_all_rows(std::string key="[unset-key]", std::string value="[unset-value]");
      std::vector<std::map<std::string, std::string>> extract_rows_by_key(std::string key="[unset-key]", std::string value="[unset-value]");
      std::vector<std::map<std::string, std::string>> extract_rows_by_keys(std::string key1="[unset-key1]", std::string value1="[unset-value1]", std::string key2="[unset-key2]", std::string value2="[unset-value2]");
      void assemble_column_headers(int num_rows_of_column_headers=2);
   };
}



