

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
#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Achievements::Achievements(AllegroFlare::FontBin* font_bin, float scrollbar_dest_position)
   : AllegroFlare::Screens::Base("Achievements")
   , font_bin(font_bin)
   , scrollbar_dest_position(scrollbar_dest_position)
   , achievements_list({})
   , initialized(false)
{
}


Achievements::~Achievements()
{
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

void Achievements::move_cursor_up()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "move_cursor_up" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   scrollbar_dest_position -= 36.0f;
   return;
}

void Achievements::move_cursor_down()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "move_cursor_down" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   scrollbar_dest_position += 36.0f;
   return;
}

void Achievements::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (button_num == VirtualControls::get_BUTTON_UP()) move_cursor_up();
   if (button_num == VirtualControls::get_BUTTON_DOWN()) move_cursor_down();
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
} // namespace Screens
} // namespace AllegroFlare


