

#include <AllegroFlare/CSVParser.hpp>

#include <sstream>
#include <vector>


namespace AllegroFlare
{


CSVParser::CSVParser()
   : csv_content("[unset-csv_content]")
   , parsed_content({})
{
}


CSVParser::~CSVParser()
{
}


std::vector<std::string> CSVParser::parse_row(std::string line)
{
   std::vector<std::string> columns;
   std::stringstream ss(line);
   std::string column;

   while (std::getline(ss, column, ',')) {
      // Handle nested commas and escaped quotes
      bool inQuotes = false;
      size_t i = 0;

      while (i < column.length())
      {
         if (column[i] == '"') {
             inQuotes = !inQuotes;

             // Handle escaped quotes
             if (i > 0 && column[i - 1] == '\\' && inQuotes) {
                 column.erase(i - 1, 1);
             }
         }

         // Remove escape characters
         if (column[i] == '\\' && i + 1 < column.length())
         {
            column.erase(i, 1);
         }

         ++i;
      }

      columns.push_back(column);
   }

   return columns;
}


} // namespace AllegroFlare


