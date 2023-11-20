

#include <AllegroFlare/CSVParser.hpp>

#include <iostream>
#include <sstream>
#include <vector>


namespace AllegroFlare
{


CSVParser::CSVParser(std::string raw_csv_content)
   : raw_csv_content(raw_csv_content)
   , parsed_content({})
{
}


CSVParser::~CSVParser()
{
}


std::vector<std::vector<std::string>> CSVParser::get_parsed_content() const
{
   return parsed_content;
}


void CSVParser::parse()
{
   parsed_content.clear();
   std::stringstream ss;
   ss.str(raw_csv_content);
   int line_num = 0;
   std::string line;
   while (std::getline(ss, line))
   {
      //std::cout << line << std::endl;
      std::vector<std::string> parsed_row = parse_row(line);
      // TODO: Validate size
      parsed_content.push_back(parsed_row);
      line_num++;
   }
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


