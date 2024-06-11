
#include <gtest/gtest.h>

#include <AllegroFlare/CSVParser.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>
#include <filesystem>


class AllegroFlare_CSVParserTest: public ::testing::Test {};

class AllegroFlare_CSVParserTestWithLoadedFixture : public ::testing::Test
{
public:
   AllegroFlare::CSVParser csv_parser;

   void load_fixture_file(std::string fixture_filename)
   {
      AllegroFlare::DeploymentEnvironment deployment_environment("test");
      std::string fixture_path = deployment_environment.get_data_folder_path();
      std::string FIXTURE_FILE = fixture_path + fixture_filename;
      ASSERT_EQ(true, std::filesystem::exists(FIXTURE_FILE));
      std::string content = AllegroFlare::php::file_get_contents(FIXTURE_FILE);
      EXPECT_EQ(false, content.empty());
      csv_parser.set_raw_csv_content(content);
      csv_parser.parse();
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

   std::vector<std::string> expected_columns = { "Name", "Age", "Address", "City, State", "Country" };
   std::vector<std::string> columns = csv_parser.parse_row(line);

   EXPECT_EQ(expected_columns, columns);
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
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string FIXTURE_FILE = fixture_path + "csv/game_content_csv.csv";

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


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, num_raw_rows__will_return_the_expected_number_of_rows)
{
   load_fixture_file("csv/game_content_csv.csv");
   EXPECT_EQ(209, csv_parser.num_raw_rows());

}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, num_columns__will_return_the_expected_number_of_columns)
{
   load_fixture_file("csv/game_content_csv.csv");
   EXPECT_EQ(33, csv_parser.num_columns());
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture,
   num_records__when_there_are_no_column_headers_present__will_return_the_expected_number_of_records)
{
   load_fixture_file("csv/game_content_csv.csv");
   EXPECT_EQ(209, csv_parser.num_records());
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, assemble_column_headers__will_not_blow_up)
{
   load_fixture_file("csv/game_content_csv2.csv");
   csv_parser.assemble_column_headers(2);
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture,
   num_records__when_column_headers_are_assembled__will_return_the_expected_number_of_records)
{
   load_fixture_file("csv/game_content_csv.csv");
   csv_parser.assemble_column_headers(2);
   EXPECT_EQ(207, csv_parser.num_records());
}


TEST_F(AllegroFlare_CSVParserTest, assemble_column_headers__will_assemble_headers_associated_with_column_numbers)
{
   std::string raw_csv_content =
      "Name,LastName,Address,\"City, State\",Age\n"
      "John,Doe,\"123, Main St\",\"This is a string\",42\n"
      "Jane,Dall,\"321, Happyberry Ave\",\"This is another string here\",64\n"
      ;
   AllegroFlare::CSVParser csv_parser(raw_csv_content);
   csv_parser.parse();

   csv_parser.assemble_column_headers(1);
   std::map<std::string, int> expected_column_headers = {
      { "Name", 0 },
      { "LastName", 1 },
      { "Address", 2 },
      { "City, State", 3 },
      { "Age", 4 },
   };
   std::map<std::string, int> actual_column_headers = csv_parser.get_column_headers();

   EXPECT_EQ(expected_column_headers, actual_column_headers);
}


TEST_F(AllegroFlare_CSVParserTest,
   assemble_column_headers__will_assemble_headers_spaning_multiple_lines)
{
   std::string raw_csv_content =
      "Name,,Address,\"City, State\",Age\n"
      "First,Last,,,\n"
      "John,Doe,\"123, Main St\",\"This is a string\",42\n"
      "Jane,Dall,\"321, Happyberry Ave\",\"This is another string here\",64\n"
      ;
   AllegroFlare::CSVParser csv_parser(raw_csv_content);
   csv_parser.parse();

   csv_parser.assemble_column_headers(2);
   std::map<std::string, int> expected_column_headers = {
      { "Name__First", 0 },
      { "Name__Last", 1 },
      { "Address", 2 },
      { "City, State", 3 },
      { "Age", 4 },
   };
   std::map<std::string, int> actual_column_headers = csv_parser.get_column_headers();

   EXPECT_EQ(expected_column_headers, actual_column_headers);
}


TEST_F(AllegroFlare_CSVParserTest,
   DISABLED__assemble_column_headers__will_assemble_collapse_column_headers_when_multiple_header_rows_are_present)
{
   std::string raw_csv_content =
     //0    1    2       3     4   5           6 7    8
      "Name ,    ,Address,     ,Age,Coordinates, ,    , \n"
      "First,Last,City   ,State,   ,Home       , ,Work, \n"
      "     ,    ,       ,     ,   ,x          ,y,x   ,y\n"
      ;
   AllegroFlare::CSVParser csv_parser(raw_csv_content);
   csv_parser.parse();

   csv_parser.assemble_column_headers(3);
   std::map<std::string, int> expected_column_headers = {
      { "Address__City", 2 },
      { "Address__State", 3 },
      { "Name__First", 0 },
      { "Name__Last", 1 },
      { "Age", 4 },
      { "Coordinates__Home__x", 5 },
      { "Coordinates__Home__y", 6 },
      { "Coordinates__Work__x", 7 },
      { "Coordinates__Work__y", 8 },
   };
   std::map<std::string, int> actual_column_headers = csv_parser.get_column_headers();

   EXPECT_EQ(expected_column_headers, actual_column_headers);
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, assemble_column_headers__will_work_with_large_test_fixture)
{
   load_fixture_file("csv/game_content_csv2.csv");

   csv_parser.assemble_column_headers(2);
   std::map<std::string, int> expected_column_headers = {
      { "Card, Location, Event", 0 }, 
      { "description", 1 }, 
      { "type", 2 }, 
      { "creation__stress", 3 }, 
      { "creation__health", 4 }, 
      { "creation__happiness", 5 }, 
      { "creation__wealth", 6 }, 
      { "creation__custom", 7 }, 
      { "upkeep__stress", 8 }, 
      { "upkeep__health", 9 }, 
      { "upkeep__happiness", 10 }, 
      { "upkeep__wealth", 11 },
      { "upkeep__custom", 12 }, 
      { "destruction__stress", 13 }, 
      { "destruction__health", 14 }, 
      { "destruction__happiness", 15 }, 
      { "destruction__wealth", 16 }, 
      { "destruction__custom", 17 }, 
      { "upkeep__rate", 18 }, 
      { "upkeep__fail_if", 19 }, 
      { "upkeep__completes_if", 20 }, 
      { "upkeep__expires_after", 21 }, 
      { "probability", 22 }, 
      { "limits__count", 23 }, 
      { "limits__frequency_in_turns", 24 }, 
      { "limits__only_if_states", 25 }, 
      { "limits__not_if_states", 26 }, 
      { "limits__only_if_foundation", 27 }, 
      { "limits__not_if_foundation", 28 }, 
      { "description_text", 29 }, 
      { "description_subtext", 30 }, 
      { "notes", 31 },
   };
   std::map<std::string, int> actual_column_headers = csv_parser.get_column_headers();

   EXPECT_EQ(expected_column_headers, actual_column_headers);
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, extract_rows_by_key__will_return_rows_that_match_the_key_value)
{
   load_fixture_file("csv/game_content_csv2.csv");
   csv_parser.assemble_column_headers(2);

   std::vector<std::map<std::string, std::string>> extracted_rows =
      csv_parser.extract_rows_by_key("type", "requirement");

   EXPECT_EQ(2, extracted_rows.size());

   // Confirm the extracted rows have the type as requested
   for (auto &col : extracted_rows[0])
   {
      EXPECT_EQ("requirement", extracted_rows[0]["type"]);
   }
}


TEST_F(AllegroFlare_CSVParserTestWithLoadedFixture, extract_rows_by_keys__will_return_rows_that_match_the_key_value)
{
   load_fixture_file("csv/game_content_csv2.csv");
   csv_parser.assemble_column_headers(2);

   std::vector<std::map<std::string, std::string>> extracted_rows =
      csv_parser.extract_rows_by_keys("type", "location", "type", "action");

   EXPECT_EQ(113, extracted_rows.size());

   // Confirm the extracted rows are the expected ones
   EXPECT_EQ("Travel Agency", extracted_rows[0]["Card, Location, Event"]);
   EXPECT_EQ("Become a Member", extracted_rows[112]["Card, Location, Event"]);
}


