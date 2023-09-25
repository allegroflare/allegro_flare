

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
   , advancing_text()
   , breakout_list_box()
   , showing_breakout_list_box(false)
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


void Choice::start()
{
   // TODO: Implement this, considering its relationship to "created_at"
   return;
}

void Choice::update()
{
   advancing_text.update();
   // NOTE: Refactoring when this method is created; expecting that nothing is to be done here
   return;
}

AllegroFlare::Elements::ListBox* Choice::get_breakout_list_box()
{
   if (!showing_breakout_list_box) return nullptr;
   return &breakout_list_box;
}

void Choice::reveal_breakout_list_box()
{
   if (!showing_breakout_list_box)
   {
      float time_now = al_get_time();
      breakout_list_box.set_created_at(time_now);
      showing_breakout_list_box = true;
   }
   return;
}

void Choice::advance()
{
   // TODO: rather than have this "finish" it should advance the animation to the end.  Then, if the dialog
   // has "advance()" called a second time, it will set finished to true.
   // NOTE: this is similar behavior to DialogBoxes/YouGotAnItem, it should be updated accordingly as well
   if (get_finished()) return;
   if (!advancing_text.get_all_characters_are_revealed())
   {
      advancing_text.reveal_all_characters();
      reveal_breakout_list_box();
      // TODO: Consider playing a tone
   }
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
      advancing_text.set_text(prompt);
      advancing_text.start(); // TODO: Consider moving this to "start()", Consider removing al_is_system_installed()
      cursor_position = 0;
   }
   initialized = true;
   return;
}

std::string Choice::get_prompt_full_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_prompt_full_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_prompt_full_text: error: guard \"initialized\" not met");
   }
   return prompt;
}

std::string Choice::get_prompt_revealed_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Choice::get_prompt_revealed_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::get_prompt_revealed_text: error: guard \"initialized\" not met");
   }
   return advancing_text.generate_revealed_text();
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

std::vector<std::string> Choice::get_item_labels()
{
   std::vector<std::string> result;
   for (auto &item : options)
   {
      result.push_back(item.first);
   }
   return result;
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


