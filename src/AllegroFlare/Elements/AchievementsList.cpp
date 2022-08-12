

#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


AchievementsList::AchievementsList(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<bool, std::string, std::string>> achievements, float achievements_box_height, float achievements_box_width)
   : font_bin(font_bin)
   , achievements(achievements)
   , achievements_box_height(achievements_box_height)
   , achievements_box_width(achievements_box_width)
{
}


AchievementsList::~AchievementsList()
{
}


void AchievementsList::set_achievements(std::vector<std::tuple<bool, std::string, std::string>> achievements)
{
   this->achievements = achievements;
}


void AchievementsList::set_achievements_box_height(float achievements_box_height)
{
   this->achievements_box_height = achievements_box_height;
}


void AchievementsList::set_achievements_box_width(float achievements_box_width)
{
   this->achievements_box_width = achievements_box_width;
}


std::vector<std::tuple<bool, std::string, std::string>> AchievementsList::get_achievements()
{
   return achievements;
}


float AchievementsList::get_achievements_box_height()
{
   return achievements_box_height;
}


float AchievementsList::get_achievements_box_width()
{
   return achievements_box_width;
}


void AchievementsList::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   float x = 0;
   float y = 0;
   float y_spacing = 30;
   for (int i=0; i<achievements.size(); i++)
   {
      bool is_achieved = std::get<0>(achievements[i]);
      std::string name = std::get<1>(achievements[i]);
      std::string description = std::get<2>(achievements[i]);
      draw_achievement_box(x, y + i * y_spacing);
   }
   return;
}

void AchievementsList::draw_achievement_box(float x, float y)
{
   float achievements_box_width = 300.0f;
   float achievements_box_height = 80.0f;
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   al_draw_filled_rectangle(x, y, x + achievements_box_width, y + achievements_box_height, box_color);
   return;
}

ALLEGRO_FONT* AchievementsList::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf -32");
}
} // namespace Elements
} // namespace AllegroFlare


