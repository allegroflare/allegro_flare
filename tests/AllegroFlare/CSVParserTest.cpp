
#include <gtest/gtest.h>

#include <AllegroFlare/CSVParser.hpp>


TEST(AllegroFlare_CSVParserTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CSVParser csvparser;
}


TEST(AllegroFlare_CSVParserTest, parse_row__returns_the_row_parsed_into_tokens)
{
   AllegroFlare::CSVParser csv_parser;
   std::string line = "Name,Age,Address,\"City, State\",Country";
   std::vector<std::string> columns = csv_parser.parse_row(line);

   // Print the parsed columns
   for (const auto& col : columns)
   {
       std::cout << col << std::endl;
   }
}

