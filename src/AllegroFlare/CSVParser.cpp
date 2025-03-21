

#include <AllegroFlare/CSVParser.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace AllegroFlare
{


CSVParser::CSVParser(std::string raw_csv_content)
   : raw_csv_content(raw_csv_content)
   , parsed_content({})
   , num_header_rows(0)
   , column_headers()
   , loaded(false)
   , column_headers_assembled(false)
   , parsed(false)
{
}


CSVParser::~CSVParser()
{
}


std::map<std::string, int> CSVParser::get_column_headers() const
{
   return column_headers;
}


bool CSVParser::get_column_headers_assembled() const
{
   return column_headers_assembled;
}


bool CSVParser::get_parsed() const
{
   return parsed;
}


void CSVParser::set_raw_csv_content(std::string raw_csv_content)
{
   this->raw_csv_content = raw_csv_content;
   parsed = false;
   parsed_content.clear();
   return;
}

int CSVParser::num_raw_rows()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::num_raw_rows]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::num_raw_rows]: error: guard \"parsed\" not met");
   }
   return parsed_content.size();
}

int CSVParser::num_rows()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::num_rows]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::num_rows]: error: guard \"parsed\" not met");
   }
   return num_records();
}

int CSVParser::num_records()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::num_records]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::num_records]: error: guard \"loaded\" not met");
   }
   return num_raw_rows() - num_header_rows;
}

int CSVParser::num_columns()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::num_columns]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::num_columns]: error: guard \"parsed\" not met");
   }
   if (parsed_content.empty()) return 0;
   return parsed_content[0].size();
}

std::vector<std::vector<std::string>> CSVParser::get_parsed_content()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::get_parsed_content]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::get_parsed_content]: error: guard \"parsed\" not met");
   }
   return parsed_content;
}

void CSVParser::parse()
{
   if (!((!parsed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::parse]: error: guard \"(!parsed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::parse]: error: guard \"(!parsed)\" not met");
   }
   parsed_content.clear();
   std::stringstream ss;
   ss.str(raw_csv_content);
   int line_num = 0;
   std::string line;
   int num_columns = -1;
   while (std::getline(ss, line))
   {
      std::vector<std::string> parsed_row = parse_row(line);
      if (num_columns == -1) num_columns = parsed_row.size();
      if (parsed_row.size() != num_columns)
      {
         // TODO: Test this throw
         std::stringstream error_message;
         error_message
               << "The number of columns must be the same on all rows. "
               << "The first row contained \"" << num_columns << "\", However the row \""
               << (line_num+1) << "\" containes \"" << parsed_row.size() << "\" columns.";
         AllegroFlare::Logger::throw_error("AllegroFlare::CSVParser", error_message.str());
      }

      parsed_content.push_back(parsed_row);
      line_num++;
   }
   parsed = true;
   loaded = true;
   column_headers_assembled = false;
   return;
}

std::vector<std::string> CSVParser::parse_row(std::string line)
{
   ParseState state = ParseState::NORMAL;
   std::string token;
   std::vector<std::string> tokens;

   for (char ch : line)
   {
      switch (state)
      {
         case ParseState::NORMAL: {
            if (ch == '"') {
               state = ParseState::INSIDE_QUOTES;
            } else if (ch == ',') {
               // Process the token
               tokens.push_back(AllegroFlare::php::trim(token));
               token.clear();
            } else {
               token += ch;
            }
            break;
         } break;

         case ParseState::INSIDE_QUOTES: {
            if (ch == '"') {
               state = ParseState::NORMAL;
            } else {
               token += ch;
            }
            break;
         } break;
      }
   }

   // Process the last token
   tokens.push_back(AllegroFlare::php::trim(token));

   return tokens;
}

int CSVParser::get_num_header_rows()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::get_num_header_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::get_num_header_rows]: error: guard \"loaded\" not met");
   }
   if (!(column_headers_assembled))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::get_num_header_rows]: error: guard \"column_headers_assembled\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::get_num_header_rows]: error: guard \"column_headers_assembled\" not met");
   }
   return num_header_rows;
}

int CSVParser::get_column_header_column_num_or_throw(std::string column_header_name)
{
   if (!(column_header_exists(column_header_name)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::get_column_header_column_num_or_throw]: error: guard \"column_header_exists(column_header_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::get_column_header_column_num_or_throw]: error: guard \"column_header_exists(column_header_name)\" not met");
   }
   return column_headers[column_header_name];
}

bool CSVParser::column_header_exists(std::string column_header_name)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::column_header_exists]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::column_header_exists]: error: guard \"loaded\" not met");
   }
   if (!(column_headers_assembled))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::column_header_exists]: error: guard \"column_headers_assembled\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::column_header_exists]: error: guard \"column_headers_assembled\" not met");
   }
   return (column_headers.count(column_header_name) > 0);
}

std::vector<std::map<std::string, std::string>> CSVParser::extract_all_rows(std::string key, std::string value)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_all_rows]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_all_rows]: error: guard \"loaded\" not met");
   }
   if (!(column_headers_assembled))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_all_rows]: error: guard \"column_headers_assembled\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_all_rows]: error: guard \"column_headers_assembled\" not met");
   }
   AllegroFlare::CSVParser &parser = *this;

   std::vector<std::map<std::string, std::string>> result;
   std::vector<std::vector<std::string>> parsed_content = parser.get_parsed_content();

   for (int row_num=num_header_rows; row_num<parsed_content.size(); row_num++)
   {
      std::map<std::string, std::string> this_row_mapped;
      for (int column_num=0; column_num<parser.num_columns(); column_num++)
      {
         for (auto &column_header : column_headers)
         {
            // TODO: Confirm not clobbering key
            this_row_mapped[column_header.first] = parsed_content[row_num][column_header.second];
         }
      }
      result.push_back(this_row_mapped);
   }
   return result;
}

std::vector<std::map<std::string, std::string>> CSVParser::extract_rows_by_key(std::string key, std::string value)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_rows_by_key]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_rows_by_key]: error: guard \"loaded\" not met");
   }
   if (!(column_headers_assembled))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_rows_by_key]: error: guard \"column_headers_assembled\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_rows_by_key]: error: guard \"column_headers_assembled\" not met");
   }
   AllegroFlare::CSVParser &parser = *this;

   std::vector<std::map<std::string, std::string>> result;
   int key_column_num = get_column_header_column_num_or_throw(key);
   std::cout << " Looking for column num " << key_column_num << std::endl;
   std::vector<std::vector<std::string>> parsed_content = parser.get_parsed_content();

   for (int row_num=num_header_rows; row_num<parsed_content.size(); row_num++)
   {
      std::string column_value = parsed_content[row_num][key_column_num];
      bool row_is_a_match = (parsed_content[row_num][key_column_num] == value);

      if (!row_is_a_match)
      {
         continue;
      }
      else // Row is a match
      {
         std::map<std::string, std::string> this_row_mapped;
         for (int column_num=0; column_num<parser.num_columns(); column_num++)
         {
            for (auto &column_header : column_headers)
            {
               // TODO: Confimrm
               this_row_mapped[column_header.first] = parsed_content[row_num][column_header.second];
            }
         }
         result.push_back(this_row_mapped);
      }
   }

   return result;
}

std::vector<std::map<std::string, std::string>> CSVParser::extract_rows_by_keys(std::string key1, std::string value1, std::string key2, std::string value2)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_rows_by_keys]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_rows_by_keys]: error: guard \"loaded\" not met");
   }
   if (!(column_headers_assembled))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::extract_rows_by_keys]: error: guard \"column_headers_assembled\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::extract_rows_by_keys]: error: guard \"column_headers_assembled\" not met");
   }
   AllegroFlare::CSVParser &parser = *this;

   std::vector<std::map<std::string, std::string>> result;
   int key1_column_num = get_column_header_column_num_or_throw(key1);
   int key2_column_num = get_column_header_column_num_or_throw(key2);
   std::cout << " Looking for column num " << key1_column_num << std::endl;
   std::vector<std::vector<std::string>> parsed_content = parser.get_parsed_content();

   for (int row_num=num_header_rows; row_num<parsed_content.size(); row_num++)
   {
      bool row_is_a_match = (parsed_content[row_num][key1_column_num] == value1)
                          || (parsed_content[row_num][key2_column_num] == value2)
                          ;

      if (!row_is_a_match)
      {
         continue;
      }
      else // Row is a match
      {
         std::map<std::string, std::string> this_row_mapped;
         for (int column_num=0; column_num<parser.num_columns(); column_num++)
         {
            for (auto &column_header : column_headers)
            {
               // TODO: Confirm
               this_row_mapped[column_header.first] = parsed_content[row_num][column_header.second];
            }
         }
         result.push_back(this_row_mapped);
      }
   }

   return result;
}

void CSVParser::assemble_column_headers(int num_rows_of_column_headers)
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"loaded\" not met");
   }
   if (!((num_rows_of_column_headers <= num_raw_rows())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"(num_rows_of_column_headers <= num_raw_rows())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"(num_rows_of_column_headers <= num_raw_rows())\" not met");
   }
   if (!((num_rows_of_column_headers > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"(num_rows_of_column_headers > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CSVParser::assemble_column_headers]: error: guard \"(num_rows_of_column_headers > 0)\" not met");
   }
   AllegroFlare::CSVParser &parser = *this;
   //(num_rows_of_column_headers <= parser.num_rows()), (num_rows_of_column_headers <= 2) ]

   // TODO: Test guard
   num_header_rows = num_rows_of_column_headers;
   column_headers.clear();

   // TODO: Add tests for cases where multi-row column headers will not line up as expected, and throw error.

   // TODO: Add a test test with greater than 2 rows for column headers
   // TODO: Remove this warning
   //AllegroFlare::Logger::warn_from(
      //"AllegroFlare::CSVParser",
      //"CSVParser does not properly collapse identifiers when there are more than 2 header rows. Middle colums "
         //"are not properly collapsed. You can eiter add the feature here OR you can add the extra column headers "
         //"in each \"intermediate\" header row in your sheet (the ones not the first or last)."
   //);


   // TODO: Only get the min required rows
   std::vector<std::vector<std::string>> parsed_content = get_parsed_content();
   std::vector<std::string> collapsed_column_names;
   collapsed_column_names.resize(num_columns());



   // Extract the first column of cells
   std::vector<std::string> first_column_cells;
   //std::cout << "first_column_cells:" << std::endl;
   //for (int row_num=(num_header_rows-1); row_num>=0; row_num--)
   for (int row_num=0; row_num<num_header_rows; row_num++)
   {
      std::string token = parsed_content[row_num][0];
      std::string cell_value = AllegroFlare::php::trim(token);
      first_column_cells.push_back(cell_value);
      //std::cout << "  " << row_num << " ##" << cell_value << "##" << std::endl;
   }


   std::vector<std::string> collapsed_prior_column_cells = first_column_cells;


   for (int column_num=0; column_num<num_columns(); column_num++)
   {
      std::vector<std::string> this_column_cells;
      for (int row_num=(num_header_rows-1); row_num>=0; row_num--)
      //for (int row_num=0; row_num<num_header_rows; row_num++)
      {
         std::string token = parsed_content[row_num][column_num];
         std::string cell_value = AllegroFlare::php::trim(token);
         this_column_cells.push_back(cell_value);
      }

      std::vector<std::string> final_tokens;
      bool nonempty_token_found = false;
      // From the bottom row of tokens in this column, find the first non-empty
      for (int row_num=(num_header_rows-1); row_num>=0; row_num--)
      {
         std::string token = parsed_content[row_num][column_num];
         std::string cell_value = AllegroFlare::php::trim(token);

         // If it's a non-empty cell, fill the collapsed_prior_column_cells cell with the value
         if (!cell_value.empty())
         {
            collapsed_prior_column_cells[row_num] = cell_value;
         }

         //std::string cell_value = parsed_content[row_num][column_num];
         if (!nonempty_token_found)
         {
            if (cell_value.empty())
            {
               //final_tokens.push_back("---");
               continue;
            }

            final_tokens.push_back(cell_value);
            nonempty_token_found = true;
         }
         else
         {
            if (cell_value.empty())
            {
               // Retrieve value from collapsed column and use it as the token
               std::string cell_value_to_fill = collapsed_prior_column_cells[row_num];
               //std::cout << "Collapsing, using row_num: " << row_num << " with value: ##"
                         //<< cell_value_to_fill << "## " << std::endl;
               final_tokens.push_back(cell_value_to_fill);
            }
            else
            {
               final_tokens.push_back(cell_value);
            }
         }
      }

      // For debugging, output final tokens
      //std::cout << "++++++++++ tokens START ++++++++++++" << std::endl;
      int i=(num_header_rows-1);
      for (auto &final_token : final_tokens)
      {
         //std::cout << "   " << i << " ##" << final_token << "##" << std::endl;
         i--;
      }
      std::reverse(final_tokens.begin(), final_tokens.end());
      std::string final_column_header = AllegroFlare::StringTransformer::join(&final_tokens, "__");
      //std::cout << " --- final_column_header: \"" << final_column_header << "\"" << std::endl;
      //std::cout << "++++++++++ tokens END ++++++++++++" << std::endl;

      collapsed_column_names[column_num] = final_column_header;
   }


   // Reverse the collapsed_column_names into the column_headers
   for (std::size_t column_num=0; column_num<collapsed_column_names.size(); column_num++)
   {
      // TODO: Validate unique column names
      column_headers[collapsed_column_names[column_num]] = column_num;
   }

   column_headers_assembled = true;
   return;
}


} // namespace AllegroFlare


