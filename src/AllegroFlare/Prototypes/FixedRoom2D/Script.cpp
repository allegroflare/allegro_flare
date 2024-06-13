

#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>

#include <AllegroFlare/UsefulPHP.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace FixedRoom2D
{


Script::Script(std::vector<std::string> lines)
   : lines(lines)
   , current_line_num(-1)
   , markers_index({})
   , initialized(false)
   , finished(false)
{
}


Script::~Script()
{
}


std::vector<std::string> Script::get_lines() const
{
   return lines;
}


int Script::get_current_line_num() const
{
   return current_line_num;
}


bool Script::get_finished() const
{
   return finished;
}


void Script::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::initialize]: error: guard \"(!initialized)\" not met");
   }
   markers_index = build_markers_index(lines);

   if (!lines.empty())
   {
      current_line_num = 1;
      finished = false;
   }
   else
   {
      finished = true;
   }
   initialized = true;
   return;
}

std::string Script::get_current_line_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::get_current_line_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::get_current_line_text]: error: guard \"initialized\" not met");
   }
   if (!at_valid_line()) return "";
   return lines[infer_current_line_index_num()];
}

bool Script::goto_next_line()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_next_line]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_next_line]: error: guard \"initialized\" not met");
   }
   if (at_last_line())
   {
      current_line_num = -1;
      finished = true;
      return true;
   }
   else
   {
      if (!at_valid_line()) return false;
      current_line_num++;
   }
   return !finished;
}

bool Script::goto_marker(std::string identifier)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_marker]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_marker]: error: guard \"initialized\" not met");
   }
   if (markers_index.find(identifier) == markers_index.end()) return false;
   int line_num_to_go_to = markers_index[identifier];
   goto_line_num(line_num_to_go_to);
   return true;
}

bool Script::goto_line_num(int line_num)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_line_num]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::goto_line_num]: error: guard \"initialized\" not met");
   }
   int line_index_num = line_num - 1;

   if (line_index_num < 0) return false;
   if (line_index_num >= lines.size()) return false;
   current_line_num = line_num;
   return true;
}

bool Script::at_last_line()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::FixedRoom2D::Script::at_last_line]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::FixedRoom2D::Script::at_last_line]: error: guard \"initialized\" not met");
   }
   return (!lines.empty() && (current_line_num == lines.size()));
}

bool Script::at_valid_line()
{
   if (lines.empty()) return false;
   if (infer_current_line_index_num() < 0) return false;
   if (infer_current_line_index_num() >= lines.size()) return false;
   return true;
}

int Script::infer_current_line_index_num()
{
   return current_line_num - 1;
}

std::pair<std::string, std::string> Script::parse_command_and_argument(std::string script_line)
{
   std::pair<std::string, std::string> result{"", ""};
   std::string DELIMETER = ": ";

   std::size_t pos = script_line.find(DELIMETER);

   if (pos == std::string::npos)
   {
      result.first = "";
      std::string _intermed = script_line;
      result.second = AllegroFlare::php::trim(_intermed);
   }
   else
   {
      std::string command_fragment_unsanitized = script_line.substr(0, pos);

      // TODO validate format of command (all caps, underscore, no spaces)
      // here

      std::string _intermed = command_fragment_unsanitized;
      result.first = AllegroFlare::php::trim(_intermed);
      std::string _intermed2 = script_line.substr(pos+DELIMETER.size());
      result.second = AllegroFlare::php::trim(_intermed2);
   }

   return result;
}

std::map<std::string, int> Script::build_markers_index(std::vector<std::string> script_lines)
{
   std::map<std::string, int> result;
   for (unsigned i=0; i<script_lines.size(); i++)
   {
      std::string script_line = script_lines[i];
      std::pair<std::string, std::string> command_and_argument = parse_command_and_argument(script_line);
      std::string command = command_and_argument.first;
      std::string argument = command_and_argument.second;
      int line_num = i+1;

      if (command == "MARKER")
      {
         if (result.find(argument) != result.end())
         {
            std::cout << "[FixedRoom2D::Script::build_markers_index]: WARNING: the marker "
                      << "\"" << argument << "\""
                      << "is being set on line " << line_num
                      << " but was already declared earlier on line " << result[argument] << ". "
                      << "Note that the previous marker will be overwritten to this new line number ("
                      << line_num << ").";
         }

         result[argument] = line_num;
      }
   }
   return result;
}

bool Script::is_valid_command_string(std::string command)
{
   static std::string VALID_FIRST_CHARACTER_CHARACTERS = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   static std::string VALID_SUBSEQUENT_CHARACTERS = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   // cannot be empty
   if (command.empty()) return false;

   // first character must be alpha-in-caps or underscore
   bool first_character_is_alpha_or_underscore =
      VALID_FIRST_CHARACTER_CHARACTERS.find(command[0]) != std::string::npos;
   if (!first_character_is_alpha_or_underscore) return false;

   // remaining characters must be alpha-in-caps, numeric, or underscore
   return command.find_first_not_of(VALID_SUBSEQUENT_CHARACTERS) == std::string::npos;
}


} // namespace FixedRoom2D
} // namespace Prototypes
} // namespace AllegroFlare


