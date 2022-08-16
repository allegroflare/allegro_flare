

#include <AllegroFlare/Screens/Achievements.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Achievements::Achievements(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, float scrollbar_dest_position, std::string game_event_name_to_emit_on_return)
   : AllegroFlare::Screens::Base("Achievements")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , scrollbar_dest_position(scrollbar_dest_position)
   , achievements_list({})
   , game_event_name_to_emit_on_return(game_event_name_to_emit_on_return)
   , initialized(false)
{
}


Achievements::~Achievements()
{
}


void Achievements::set_game_event_name_to_emit_on_return(std::string game_event_name_to_emit_on_return)
{
   this->game_event_name_to_emit_on_return = game_event_name_to_emit_on_return;
}


std::string Achievements::get_game_event_name_to_emit_on_return()
{
   return game_event_name_to_emit_on_return;
}


AllegroFlare::Elements::AchievementsList &Achievements::get_achievements_list_ref()
{
   return achievements_list;
}


void Achievements::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
   achievements_list.set_font_bin(font_bin);
   return;
}

void Achievements::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "set_event_emitter" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->event_emitter = event_emitter;
   return;
}

void Achievements::on_activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "on_activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   // position cursor such that it will scroll to the top
   achievements_list.set_scrollbar_position_to_max();
   move_scrollbar_position_to(0);

   // emit events to show and set the input hints
   emit_event_to_set_input_hints();
   event_emitter->emit_show_input_hints_bar_event();
   return;
}

void Achievements::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   achievements_list.set_font_bin(font_bin);
   achievements_list.set_achievements(build_achievements());
   initialized = true;
   return;
}

void Achievements::primary_timer_func()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "primary_timer_func" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   update();
   render();
   return;
}

void Achievements::update()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   float scrollbar_position = achievements_list.get_scrollbar_position();
   if (scrollbar_position != scrollbar_dest_position)
   {
      float update_rate = 0.2f;
      scrollbar_position += (scrollbar_dest_position - scrollbar_position) * update_rate;
      achievements_list.set_scrollbar_position(scrollbar_position);
   }
   return;
}

void Achievements::move_scrollbar_position_to(float position)
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "move_scrollbar_position_to" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   scrollbar_dest_position = position;
   limit_scrollbar_dest_position();
   return;
}

void Achievements::move_scrollbar_position_up()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "move_scrollbar_position_up" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   scrollbar_dest_position -= 36.0f;
   limit_scrollbar_dest_position();
   return;
}

void Achievements::move_scrollbar_position_down()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "move_scrollbar_position_down" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   scrollbar_dest_position += 36.0f;
   limit_scrollbar_dest_position();
   return;
}

void Achievements::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (button_num == VirtualControls::get_BUTTON_UP()) move_scrollbar_position_up();
   if (button_num == VirtualControls::get_BUTTON_DOWN()) move_scrollbar_position_down();
   else event_emitter->emit_game_event(game_event_name_to_emit_on_return);
}

void Achievements::render()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   achievements_list.render();
   return;
}

std::vector<std::tuple<std::string, std::string, std::string>> Achievements::build_achievements()
{
   return AllegroFlare::Elements::AchievementsList::build_placeholder_achievements();
}

void Achievements::limit_scrollbar_dest_position()
{
   float scrollbar_max_position = achievements_list.infer_scrollbar_max_position();
   scrollbar_dest_position = std::max(0.0f, std::min(scrollbar_dest_position, scrollbar_max_position));
   return;
}

void Achievements::emit_event_to_set_input_hints()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "emit_event_to_set_input_hints" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "emit_event_to_set_input_hints" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   event_emitter->emit_set_input_hints_bar_event({
      "UP", "%SPACE", "DOWN", "%SPACER", "LABEL>>", "Scroll up/down",
      "%SEPARATOR",
      "X", "%SPACER", "LABEL>>", "Return",
   });
   return;
}
} // namespace Screens
} // namespace AllegroFlare


