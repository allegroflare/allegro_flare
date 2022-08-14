

#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


Achievements::Achievements(AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base("Achievements")
   , font_bin(font_bin)
{
}


Achievements::~Achievements()
{
}


void Achievements::primary_timer_func()
{
   update();
   render();
   return;
}

void Achievements::update()
{
   return;
}

void Achievements::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Achievements" << "::" << "render" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::Elements::AchievementsList achievements_list(font_bin, build_achievements());
   achievements_list.render();
   return;
}

std::vector<std::tuple<std::string, std::string, std::string>> Achievements::build_achievements()
{
   return AllegroFlare::Elements::AchievementsList::build_placeholder_achievements();
}
} // namespace Screens
} // namespace AllegroFlare


