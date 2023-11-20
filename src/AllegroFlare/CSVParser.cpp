

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


