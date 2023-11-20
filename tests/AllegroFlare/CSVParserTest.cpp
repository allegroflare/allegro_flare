
#include <gtest/gtest.h>

#include <AllegroFlare/CSVParser.hpp>
#include <AllegroFlare/UsefulPHP.hpp> // TODO: Replace this with a test-local fixture file


class AllegroFlare_CSVParserTest: public ::testing::Test {};

class AllegroFlare_CSVParserTestWithLoadedFixture : public ::testing::Test
{
private:
   // TODO: Replace this path with a test-local fixture file
   std::string FIXTURE_FILE = "/Users/markoates/Repos/allegro_flare/tests/fixtures/csv/game_content_csv.csv";

public:
   AllegroFlare::CSVParser csv_parser;

   virtual void SetUp() override
   {
      // TODO: Validate existence of test fixture file
      std::string content = AllegroFlare::php::file_get_contents(FIXTURE_FILE);
      EXPECT_EQ(false, content.empty());
      csv_parser.set_raw_csv_content(content);
      csv_parser.parse();
   }
   virtual void TearDown() override
   {
   }
};


TEST_F(AllegroFlare_CSVParserTest, can_be_created_without_blowing_up)
{
   AllegroFlare::CSVParser csvparser;
}


TEST_F(AllegroFlare_CSVParserTest, parse_row__returns_the_row_parsed_into_tokens)
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


TEST_F(AllegroFlare_CSVParserTest,
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


TEST_F(AllegroFlare_CSVParserTest, parse__will_parse_the_content)
{
   std::string raw_csv_content =
      "Name,LastName,Address,\"City, State\",Age\n"
      "John,Doe,\"123, Main St\",\"This is a string\",42\n"
      "Jane,Dall,\"321, Happyberry Ave\",\"This is another string here\",64\n"
      ;

   AllegroFlare::CSVParser csv_parser(raw_csv_content);
   csv_parser.parse();
   std::vector<std::vector<std::string>> actual_parsed_content = csv_parser.get_parsed_content();

   EXPECT_EQ(3, actual_parsed_content.size());

   std::vector<std::vector<std::string>> expected_parsed_content = {
      {
         "Name",
         "LastName",
         "Address",
         "City, State",
         "Age"
      },
      {
         "John",
         "Doe",
         "123, Main St",
         "This is a string",
         "42"
      },
      {
         "Jane",
         "Dall",
         "321, Happyberry Ave",
         "This is another string here",
         "64"
      },
   };

   EXPECT_EQ(expected_parsed_content, actual_parsed_content);
}


TEST_F(AllegroFlare_CSVParserTest, parse__will_parse_large_content)
{
   // TODO: Replace this path with a test-local fixture file
   std::string FIXTURE_FILE = "/Users/markoates/Repos/allegro_flare/tests/fixtures/csv/game_content_csv.csv";
   // TODO: Validate existence of test fixture file
   std::string content = AllegroFlare::php::file_get_contents(FIXTURE_FILE);
   EXPECT_EQ(false, content.empty());

   AllegroFlare::CSVParser csv_parser(content);
   csv_parser.parse();

   std::vector<std::vector<std::string>> parsed_content = csv_parser.get_parsed_content();

   ASSERT_EQ(209, parsed_content.size());

   // Check some spot data
   EXPECT_EQ("Card, Location, Event", parsed_content[0][0]);
   EXPECT_EQ("happiness", parsed_content[1][6]);
   EXPECT_EQ("range+10", parsed_content[17][8]);
   EXPECT_EQ("bravery+3, persuasion+2", parsed_content[23][13]);
   EXPECT_EQ("achievement", parsed_content[208][2]);
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, num_rows__will_return_the_expected_number_of_rows)
{
   EXPECT_EQ(209, csv_parser.num_rows());

}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, num_columns__will_return_the_expected_number_of_columns)
{
   EXPECT_EQ(33, csv_parser.num_columns());
}


