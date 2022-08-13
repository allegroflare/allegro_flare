

#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


AchievementsList::AchievementsList(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<bool, std::string, std::string>> achievements, float achievements_box_width, float achievements_box_height)
   : font_bin(font_bin)
   , achievements(achievements)
   , achievements_box_width(achievements_box_width)
   , achievements_box_height(achievements_box_height)
   , surface_width(1920)
   , surface_height(1080)
{
}


AchievementsList::~AchievementsList()
{
}


void AchievementsList::set_achievements(std::vector<std::tuple<bool, std::string, std::string>> achievements)
{
   this->achievements = achievements;
}


void AchievementsList::set_achievements_box_width(float achievements_box_width)
{
   this->achievements_box_width = achievements_box_width;
}


void AchievementsList::set_achievements_box_height(float achievements_box_height)
{
   this->achievements_box_height = achievements_box_height;
}


void AchievementsList::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void AchievementsList::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


std::vector<std::tuple<bool, std::string, std::string>> AchievementsList::get_achievements()
{
   return achievements;
}


float AchievementsList::get_achievements_box_width()
{
   return achievements_box_width;
}


float AchievementsList::get_achievements_box_height()
{
   return achievements_box_height;
}


int AchievementsList::get_surface_width()
{
   return surface_width;
}


int AchievementsList::get_surface_height()
{
   return surface_height;
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
   AllegroFlare::Placement2D place(surface_width/2, surface_height/2, achievements_box_width, 900);

   float x = 0;
   float y = 0;
   float y_spacing = 150 + 10;

   place.start_transform();
   for (int i=0; i<achievements.size(); i++)
   {
      bool is_achieved = std::get<0>(achievements[i]);
      std::string title = std::get<1>(achievements[i]);
      std::string description = std::get<2>(achievements[i]);
      draw_achievement_box(x, y + i * y_spacing, is_achieved, title, description);
   }
   place.restore_transform();
   return;
}

void AchievementsList::draw_achievement_box(float x, float y, bool is_achieved, std::string title, std::string description)
{
   ALLEGRO_FONT *title_font = obtain_title_font();
   ALLEGRO_FONT *description_font = obtain_description_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   float achievements_box_width = 800.0f;
   float achievements_box_height = 150.0f;
   float box_padding_x = 20;
   float box_padding_y = 20;
   float title_padding_y = 10;
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   ALLEGRO_COLOR icon_container_box_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR icon_locked_color = ALLEGRO_COLOR{0.4, 0.405, 0.41, 1};
   ALLEGRO_COLOR icon_achieved_color = ALLEGRO_COLOR{1, 1, 1, 1};
   float title_font_line_height = al_get_font_line_height(title_font);
   float description_font_line_height = al_get_font_line_height(description_font);
   float icon_font_line_height = al_get_font_line_height(icon_font);
   float icon_container_box_size = achievements_box_height - box_padding_x*2;
   float text_y_offset = 2;
   float text_x_offset = 140;

   float icon_box_center_x = x + box_padding_x + icon_container_box_size / 2;
   float icon_box_center_y = y + box_padding_y + icon_container_box_size / 2;
   int32_t icon_character = is_achieved ? 0xf091 : 0xf023;
   ALLEGRO_COLOR icon_color = is_achieved ? icon_achieved_color : icon_locked_color;

   // draw the filled rectangle
   al_draw_filled_rectangle(x, y, x + achievements_box_width, y + achievements_box_height, box_color);

   // draw the icon container box rectangle
   al_draw_filled_rectangle(
      x + box_padding_x,
      y + box_padding_y,
      x + box_padding_x + icon_container_box_size,
      y + box_padding_y + icon_container_box_size,
      icon_container_box_color
   );

   // draw the icon
   draw_unicode_character(
      icon_font,
      icon_color,
      icon_box_center_x,
      icon_box_center_y - icon_font_line_height / 2,
      icon_character,
      ALLEGRO_ALIGN_CENTER
   );

   // draw the title text
   al_draw_text(
      title_font,
      text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + text_y_offset,
      ALLEGRO_ALIGN_LEFT,
      title.c_str()
   );

   // draw the description text
   al_draw_multiline_text(
      description_font,
      text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + title_font_line_height + title_padding_y + text_y_offset,
      500,
      description_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      description.c_str()
   );

   return;
}

std::vector<std::tuple<bool, std::string, std::string>> AchievementsList::build_placeholder_achievements()
{
   return {
      { false, "Save the Cat", "Define the hero and make the audience like them." },
      { false, "All is Lost", "Make the hero lose everything that is important." },
      { true, "Break the Fourth Wall", "Make the developer realize they're looking at test data." },
   };
}

ALLEGRO_FONT* AchievementsList::obtain_title_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "obtain_title_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Bold.ttf -36");
}

ALLEGRO_FONT* AchievementsList::obtain_description_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "obtain_description_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("Inter-Medium.ttf -28");
}

ALLEGRO_FONT* AchievementsList::obtain_icon_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AchievementsList" << "::" << "obtain_icon_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("fa-solid-900.ttf -50");
}

void AchievementsList::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}
} // namespace Elements
} // namespace AllegroFlare


