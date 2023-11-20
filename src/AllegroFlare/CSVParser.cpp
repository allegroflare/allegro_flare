

#include <AllegroFlare/CSVParser.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace AllegroFlare
{


CSVParser::CSVParser(std::string raw_csv_content)
   : raw_csv_content(raw_csv_content)
   , parsed_content({})
   , parsed(false)
{
}


CSVParser::~CSVParser()
{
}


bool CSVParser::get_parsed() const
{
   return parsed;
}


int CSVParser::num_rows()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[CSVParser::num_rows]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CSVParser::num_rows: error: guard \"parsed\" not met");
   }
   return parsed_content.size();
}

int CSVParser::num_columns()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[CSVParser::num_columns]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CSVParser::num_columns: error: guard \"parsed\" not met");
   }
   if (parsed_content.empty()) return 0;
   return parsed_content[0].size();
}

void CSVParser::set_raw_csv_content(std::string raw_csv_content)
{
   this->raw_csv_content = raw_csv_content;
   parsed = false;
   parsed_content.clear();
   return;
}

std::vector<std::vector<std::string>> CSVParser::get_parsed_content()
{
   if (!(parsed))
   {
      std::stringstream error_message;
      error_message << "[CSVParser::get_parsed_content]: error: guard \"parsed\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CSVParser::get_parsed_content: error: guard \"parsed\" not met");
   }
   return parsed_content;
}

void CSVParser::parse()
{
   if (!((!parsed)))
   {
      std::stringstream error_message;
      error_message << "[CSVParser::parse]: error: guard \"(!parsed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CSVParser::parse: error: guard \"(!parsed)\" not met");
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
         error_message << "The first row contained \"" << num_columns << "\", However the row \""
               << (line_num+1) << "\" containes \"" << parsed_row.size() << "\" columns. The number "
                  "of columns must be the same on all rows.";
         AllegroFlare::Logger::throw_error("AllegroFlare::CSVParser", error_message.str());
      }

      parsed_content.push_back(parsed_row);
      line_num++;
   }
   parsed = true;
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
               tokens.push_back(token);
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
   tokens.push_back(token);

   return tokens;
}


} // namespace AllegroFlare


