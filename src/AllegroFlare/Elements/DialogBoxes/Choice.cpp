

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
   , advancing_text()
   , breakout_list_box()
   , showing_breakout_list_box(false)
   , showing_cursor(false)
   , initialized(false)
{
}


Choice::~Choice()
{
}


bool Choice::get_showing_breakout_list_box() const
{
   return showing_breakout_list_box;
}


bool Choice::get_showing_cursor() const
{
   return showing_cursor;
}


void Choice::start()
{
   // TODO: Implement this, considering its relationship to "created_at"
   throw std::runtime_error("DialogBoxes::Choice::start not implemented");
   return;
}

void Choice::update()
{
   if (!advancing_text.get_all_characters_are_revealed())
   {
      advancing_text.update();
      if (advancing_text.get_all_characters_are_revealed())
      {
         reveal_breakout_list_box();
         // TODO: Consider playing a tone
      }
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
      // TODO: Consider what behavior is expected here when there are no options. Maybe throw in the mean time
   }
   else
   {
      // Initialize the advancing_text element
      advancing_text.set_text(prompt);
      advancing_text.start(); // TODO: Consider moving this to "start()", Consider removing al_is_system_installed()

      // Initialize the breakout_list_box element
      breakout_list_box.set_items(options);
      breakout_list_box.set_wrap_at_edges(true);
   }
   initialized = true;
   return;
}

void Choice::set_prompt(std::string prompt)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Choice::set_prompt]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::set_prompt: error: guard \"(!initialized)\" not met");
   }
   this->prompt = prompt;
   return;
}

void Choice::set_options(std::vector<std::pair<std::string, std::string>> options)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Choice::set_options]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Choice::set_options: error: guard \"(!initialized)\" not met");
   }
   this->options = options;
   return;
}

void Choice::reveal_breakout_list_box()
{
   if (!showing_breakout_list_box)
   {
      float time_now = al_get_time();
      breakout_list_box.set_created_at(time_now);
      showing_breakout_list_box = true;
      showing_cursor = true; // For now, using this "showing_cursor" mechanism.  Might consider using a different
                             // mechanism that sends info to an injected cursor
   }
   return;
}

float Choice::infer_breakout_list_box_age()
{
   if (!showing_breakout_list_box) return 0;
   float time_now = al_get_time(); // TODO: Consider injecting a "time_now"
   return breakout_list_box.infer_age(time_now);
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

std::vector<std::string> Choice::get_options_labels()
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
   return breakout_list_box.get_currently_selected_item_label();
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
   return breakout_list_box.get_currently_selected_item_value();
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
   breakout_list_box.move_cursor_down();
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
   breakout_list_box.move_cursor_up();
   return;
}

bool Choice::has_valid_cursor_position()
{
   return breakout_list_box.has_valid_currently_selected_item();
}

int Choice::get_cursor_position()
{
   return breakout_list_box.get_cursor_position();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


