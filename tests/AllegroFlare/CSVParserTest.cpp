
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

   EXPECT_EQ(5, columns.size());

   //TODO: Assert parsed_tokens

   // Debug: Print the parsed columns
   for (const auto& col : columns)
   {
       std::cout << col << std::endl;
   }
}


TEST(AllegroFlare_CSVParserTest,
   DISABLED__parse_row__will_account_for_quoted_tokens_and_escaped_quotes_within_quoted_tokens)
{
   // TODO: Enable quotes within quoted string tokens
   AllegroFlare::CSVParser csv_parser;
   std::string line = "John,Doe,\"123, Main St\",\"This is a \"\"quoted\"\" string\",42";
   std::vector<std::string> columns = csv_parser.parse_row(line);

   EXPECT_EQ(5, columns.size());

   std::vector<std::string> expected_parsed_tokens = {
      "John",
      "Doe",
      "123, Main St",
      "This is a \"quoted\" string",
      "42"
   };

   EXPECT_EQ(columns, expected_parsed_tokens);
   // Debug: Print the parsed columns
   for (const auto& col : columns)
   {
       std::cout << col << std::endl;
   }
}


TEST(AllegroFlare_CSVParserTest, parse__will_parse_the_content)
{
   std::string raw_csv_content =
      "Name,LastName,Address,\"City, State\",Age\n"
      "John,Doe,\"123, Main St\",\"This is a \"\"quoted\"\" string\",42\n"
      "Jane,Dall,\"321, Happyberry Ave\",\"This \"\"quoted\"\" string is here\",64\n"
      ;

   AllegroFlare::CSVParser csv_parser(raw_csv_content);
   csv_parser.parse();
   std::vector<std::vector<std::string>> parsed_content = csv_parser.get_parsed_content();

   //EXPECT_EQ(3, parsed_content.size());

   //TODO: Assert parsed_tokens

   // Debug: Print the parsed columns
   //for (const auto& col : parsed_content)
   //{
       //std::cout << col << std::endl;
   //}
}


