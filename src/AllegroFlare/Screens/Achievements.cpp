

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


Achievements::Achievements(AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::Achievements* achievements, float scrollbar_dest_position, std::string game_event_name_to_emit_on_return)
   : AllegroFlare::Screens::Base("Achievements")
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , achievements(achievements)
   , scrollbar_dest_position(scrollbar_dest_position)
   , achievements_list({})
   , game_event_name_to_emit_on_return(game_event_name_to_emit_on_return)
   , initialized(false)
{
}


Achievements::~Achievements()
{
}


void Achievements::set_achievements(AllegroFlare::Achievements* achievements)
{
   this->achievements = achievements;
}


void Achievements::set_game_event_name_to_emit_on_return(std::string game_event_name_to_emit_on_return)
{
   this->game_event_name_to_emit_on_return = game_event_name_to_emit_on_return;
}


std::string Achievements::get_game_event_name_to_emit_on_return() const
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

void Achievements::refresh_achievements_list()
{
   std::vector<std::tuple<std::string, std::string, std::string>> result;
   for (auto &achievement : achievements->get_achievements())
   {
      AllegroFlare::Achievement *ach = std::get<0>(achievement.second);
      bool unlocked = std::get<1>(achievement.second);
      bool hidden = std::get<2>(achievement.second);
      // TODO: test this
      std::string status = unlocked ? "unlocked" : (hidden ? "hidden" : "locked" );
      result.push_back({ status, ach->get_title(), ach->get_description() });
   }
   achievements_list.set_achievements(result);
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
   // refresh the achievements from the actual list of achievements
   refresh_achievements_list();

   // position cursor such that it will scroll to the top
   achievements_list.set_scrollbar_position_to_max();
   move_scrollbar_position_to(0);

   // emit events to show and set the input hints
   emit_event_to_set_input_hints();
   event_emitter->emit_show_input_hints_bar_event();
   return;
}

void Achievements::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Achievements" << "::" << "on_deactivate" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   // emit events to show and set the input hints
   // TODO: add ALLEGRO_FLARE_EVENT_CLEAR_INPUT_HINTS_BAR
   event_emitter->emit_set_input_hints_bar_event({});
   event_emitter->emit_hide_input_hints_bar_event();
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
   if (!(achievements))
   {
      std::stringstream error_message;
      error_message << "Achievements" << "::" << "initialize" << ": error: " << "guard \"achievements\" not met";
      throw std::runtime_error(error_message.str());
   }
   achievements_list.set_font_bin(font_bin);
   refresh_achievements_list();
   //achievements_list.set_achievements(build_achievements());
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

void Achievements::set_placeholder_achievements()
{
   return achievements_list.set_achievements(build_achievements());
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
   std::vector<std::string> scrollbar_tokens = { "UP", "%SPACE", "DOWN", "%SPACER", "LABEL>>", "Scroll up/down", };
   std::vector<std::string> return_tokens = { "X", "%SPACER", "LABEL>>", "Return", };
   std::vector<std::string> separator_tokens = { "%SEPARATOR" };
   std::vector<std::string> result_tokens;

   if (infer_scrollbar_is_showing())
   {
      result_tokens.insert(result_tokens.end(), scrollbar_tokens.begin(), scrollbar_tokens.end());
      result_tokens.insert(result_tokens.end(), separator_tokens.begin(), separator_tokens.end());
   }

   result_tokens.insert(result_tokens.end(), return_tokens.begin(), return_tokens.end());

   event_emitter->emit_set_input_hints_bar_event(result_tokens);
   return;
}

bool Achievements::infer_scrollbar_is_showing()
{
   return !achievements_list.scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container();
}
} // namespace Screens
} // namespace AllegroFlare


