

#include <AllegroFlare/Elements/DialogBoxes/Choice.hpp>

#include <AllegroFlare/Logger.hpp>
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
   , speaking_character("")
   , advancing_text()
   , breakout_list_box()
   , breakout_list_box_active(false)
   , cursor_active(false)
   , initialized(false)
{
}


Choice::~Choice()
{
}


void Choice::set_speaking_character(std::string speaking_character)
{
   this->speaking_character = speaking_character;
}


std::string Choice::get_speaking_character() const
{
   return speaking_character;
}


bool Choice::get_breakout_list_box_active() const
{
   return breakout_list_box_active;
}


bool Choice::get_cursor_active() const
{
   return cursor_active;
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
   else if (breakout_list_box_active)
   {
      set_finished(true); // TODO: Look into if this is needed here or where it should be placed
      // TODO: Consider playing a tone
   }
   else
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Elements::DialogBoxes::Choice::advance",
            "Reached unexpected branching path"
         );
   }
   return;
}

void Choice::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::initialize]: error: guard \"(!initialized)\" not met");
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

bool Choice::has_speaking_character()
{
   return (!speaking_character.empty());
}

void Choice::set_prompt(std::string prompt)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::set_prompt]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::set_prompt]: error: guard \"(!initialized)\" not met");
   }
   this->prompt = prompt;
   return;
}

void Choice::set_options(std::vector<std::pair<std::string, std::string>> options)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::set_options]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::set_options]: error: guard \"(!initialized)\" not met");
   }
   this->options = options;
   return;
}

void Choice::reveal_breakout_list_box()
{
   if (!breakout_list_box_active)
   {
      float time_now = al_get_time();
      breakout_list_box.set_created_at(time_now);
      breakout_list_box_active = true;
      cursor_active = true; // For now, using this "cursor_active" mechanism.  Might consider using a different
                            // mechanism that sends info to an injected cursor
   }
   return;
}

float Choice::infer_breakout_list_box_age()
{
   if (!breakout_list_box_active) return 0;
   float time_now = al_get_time(); // TODO: Consider injecting a "time_now"
   return breakout_list_box.infer_age(time_now);
}

std::string Choice::get_prompt_full_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::get_prompt_full_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::get_prompt_full_text]: error: guard \"initialized\" not met");
   }
   return prompt;
}

std::string Choice::get_prompt_revealed_text()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::get_prompt_revealed_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::get_prompt_revealed_text]: error: guard \"initialized\" not met");
   }
   return advancing_text.generate_revealed_text();
}

std::vector<std::pair<std::string, std::string>> Choice::get_options()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::get_options]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::get_options]: error: guard \"initialized\" not met");
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
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::get_current_selection_text]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::get_current_selection_text]: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return "";
   return breakout_list_box.get_currently_selected_item_label();
}

std::string Choice::get_current_selection_value()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::get_current_selection_value]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::get_current_selection_value]: error: guard \"initialized\" not met");
   }
   if (!has_valid_cursor_position()) return "";
   return breakout_list_box.get_currently_selected_item_value();
}

bool Choice::move_cursor_position_down()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::move_cursor_position_down]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::move_cursor_position_down]: error: guard \"initialized\" not met");
   }
   if (!breakout_list_box_active) return false; // TODO: Test this case, does not move when list box is inactive
   // TODO: Consider if empty items in breakout_list_box should result in a return false
   breakout_list_box.move_cursor_down();
   return true;
}

bool Choice::move_cursor_position_up()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::move_cursor_position_up]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::move_cursor_position_up]: error: guard \"initialized\" not met");
   }
   if (!breakout_list_box_active) return false; // TODO: Test this case, does not move when list box is inactive
   // TODO: Consider if empty items in breakout_list_box should result in a return false
   breakout_list_box.move_cursor_up();
   return true;
}

bool Choice::has_valid_cursor_position()
{
   // TODO: Test this case with the usage of "breakout_list_box_active"
   return breakout_list_box_active && breakout_list_box.has_valid_currently_selected_item();
}

void Choice::set_cursor_position(int cursor_position)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxes::Choice::set_cursor_position]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxes::Choice::set_cursor_position]: error: guard \"initialized\" not met");
   }
   // TODO: Modify this method so that an "start_cursor_position" could be provided
   // TODO: Test this method
   breakout_list_box.set_cursor_position(cursor_position);
   return;
}

int Choice::get_cursor_position()
{
   return breakout_list_box.get_cursor_position();
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare


