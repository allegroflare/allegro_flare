

#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Choice::Choice(std::string prompt, std::vector<std::pair<std::string, std::string>> options)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::Choice::TYPE)
   , prompt(prompt)
   , options(options)
   , cursor_position(-1)
   , initialized(false)
{
}


Choice::~Choice()
{
}


int Choice::get_cursor_position() const
{
   return cursor_position;
}


void Choice::update()
{
   // NOTE: Refactoring when this method is created; expecting that nothing is to be done here
   return;
}

void Choice::advance()
{
   // TODO: rather than have this "finish" it should advance the animation to the end.  Then, if the dialog
   // has "advance()" called a second time, it will set finished to true.
   // NOTE: this is similar behavior to DialogBoxes/YouGotAnItem, it should be updated accordingly as well
   if (get_finished()) return;
   set_finished(true);
}

void Choice::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Choice::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::initialize: error: guard \"(!initialized)\" not met");
   }
   if (options.empty())
   {
      // do nothing
   }
   else
   {
      cursor_position = 0;
   }
   initialized = true;
   return;
}

std::string Choice::get_prompt()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_prompt]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_prompt: error: guard \"initialized\" not met");
   }
   return prompt;
}

std::vector<std::pair<std::string, std::string>> Choice::get_options()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_options]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_options: error: guard \"initialized\" not met");
   }
   return options;
}

std::string Choice::get_current_selection_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_current_selection_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_current_selection_text: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return "";
   return options[cursor_position].first;
}

std::string Choice::get_current_selection_value()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_current_selection_value]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_current_selection_value: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return "";
   return options[cursor_position].second;
}

void Choice::move_cursor_position_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::move_cursor_position_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::move_cursor_position_down: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return;

   cursor_position++;
   if (cursor_position >= options.size()) cursor_position = cursor_position % options.size();
   return;
}

void Choice::move_cursor_position_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::move_cursor_position_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::move_cursor_position_up: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return;

   cursor_position--;
   if (cursor_position < 0) cursor_position = (cursor_position + (options.size() * 100)) % options.size();
   return;
}

bool Choice::has_valid_cursor_position()
{
   return (cursor_position != -1);
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


