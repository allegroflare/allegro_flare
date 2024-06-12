

#include <AllegroFlare/Elements/AchievementsList.hpp>

#include <AllegroFlare/Elements/Scrollbar.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


AchievementsList::AchievementsList(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string, std::string>> achievements, float achievements_box_width, float achievements_box_height)
   : font_bin(font_bin)
   , achievements(achievements)
   , achievements_box_width(achievements_box_width)
   , achievements_box_height(achievements_box_height)
   , surface_width(1920)
   , surface_height(1080)
   , scrollbar_position(0.0f)
   , box_gutter_y(10.0f)
{
}


AchievementsList::~AchievementsList()
{
}


void AchievementsList::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void AchievementsList::set_achievements(std::vector<std::tuple<std::string, std::string, std::string>> achievements)
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


void AchievementsList::set_box_gutter_y(float box_gutter_y)
{
   this->box_gutter_y = box_gutter_y;
}


std::vector<std::tuple<std::string, std::string, std::string>> AchievementsList::get_achievements() const
{
   return achievements;
}


float AchievementsList::get_achievements_box_width() const
{
   return achievements_box_width;
}


float AchievementsList::get_achievements_box_height() const
{
   return achievements_box_height;
}


int AchievementsList::get_surface_width() const
{
   return surface_width;
}


int AchievementsList::get_surface_height() const
{
   return surface_height;
}


float AchievementsList::get_scrollbar_position() const
{
   return scrollbar_position;
}


float AchievementsList::get_box_gutter_y() const
{
   return box_gutter_y;
}


void AchievementsList::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_achievements_list_items_and_scrollbar();
   draw_achievements_list_title_text_and_completed_title_text();
   return;
}

void AchievementsList::move_scrollbar_position(float distance_y)
{
   scrollbar_position += distance_y;
   limit_scrollbar_position();
   return;
}

void AchievementsList::set_scrollbar_position(float scrollbar_position)
{
   this->scrollbar_position = scrollbar_position;
   limit_scrollbar_position();
   return;
}

void AchievementsList::set_scrollbar_position_to_max()
{
   this->scrollbar_position = infer_container_scroll_range();
   return;
}

float AchievementsList::infer_scrollbar_max_position()
{
   return infer_container_scroll_range();
}

bool AchievementsList::scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container()
{
   return infer_container_scroll_range() <= 0;
}

std::vector<std::tuple<std::string, std::string, std::string>> AchievementsList::build_placeholder_achievements()
{
   return {
      { "unlocked", "Fade In", "Start out in the world." },
      { "locked",   "Call to Adventure", "Leave what you know in order to take on a challenge you must face." },
      { "locked",   "Save the Cat", "Define the hero and make the audience like them." },
      { "unlocked", "Break the Fourth Wall", "Make the developer realize they're looking at test data." },
      { "hidden",   "Top Secrets", "Find the box of secrets in the 2nd act." },
      { "locked",   "I'm Lovin' It", "Complete the AchievementsList feature." },
      { "unlocked", "Everyone is Beautiful", "Make multiline text fit into the box with the correct width." },
      { "hidden",   "Save the Best for Last", "Find out the most important part in the very end." },
   };
}

int AchievementsList::count_num_achievements_completed()
{
   int count = 0;
   for (int i=0; i<achievements.size(); i++)
   {
      bool is_achieved = (std::get<0>(achievements[i]) == "unlocked");
      if (is_achieved) count++;
   }
   return count;
}

void AchievementsList::draw_header_title_backfill()
{
   // draw inputs
   float backfill_opacity = 0.35;
   float bar_height = 160;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, backfill_opacity};
   al_draw_filled_rectangle(0, 0, surface_width, bar_height, backfill_color);
   return;
}

int AchievementsList::count_num_achievements()
{
   return achievements.size();
}

std::string AchievementsList::build_achievements_count_string()
{
   std::stringstream result;
   result << count_num_achievements_completed() << " of " << count_num_achievements()
          << " achieved";
   return result.str();
}

void AchievementsList::draw_achievements_list_title_text_and_completed_title_text()
{
   ALLEGRO_FONT *font = obtain_title_font();
   ALLEGRO_COLOR color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   float surface_padding_x = 300;

   // draw the backfill
   draw_header_title_backfill();

   // draw the title text
   al_draw_text(
      font,
      color,
      surface_padding_x,
      100,
      ALLEGRO_ALIGN_LEFT,
      "A C H I E V E M E N T S"
   );

   // draw the number achieved
   al_draw_text(
      font,
      color,
      1920-surface_padding_x,
      100,
      ALLEGRO_ALIGN_RIGHT,
      build_achievements_count_string().c_str()
   );
   return;
}

float AchievementsList::infer_container_height()
{
   return 800;
   //return (achievements_box_height + box_gutter_y) * 5.5;
}

float AchievementsList::infer_container_contents_height()
{
   float y_spacing = achievements_box_height + box_gutter_y;
   return achievements.size() * y_spacing - box_gutter_y; // <- this should be revised
                                                          // to take into account
                                                          // lists of size 0; E.g.
                                                          // Box gutter y should not
                                                          // be subtracted in that
                                                          // case
}

float AchievementsList::infer_container_scroll_range()
{
   return infer_container_contents_height() - infer_container_height();
}

void AchievementsList::limit_scrollbar_position()
{
   float y_spacing = achievements_box_height + box_gutter_y;
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   scrollbar_position = std::max(0.0f, std::min(container_scroll_range, scrollbar_position));
   return;
}

void AchievementsList::draw_achievements_list_items_and_scrollbar()
{
   float achievements_list_x = surface_width/2;
   float achievements_list_y = surface_height/2 + 40;
   float achievements_list_width = achievements_box_width;
   float scrollbar_x_padding = 70;
   float scrollbar_y_padding = 26;
   ALLEGRO_COLOR achievements_list_frame_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_bar_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_handle_color = ALLEGRO_COLOR{0.5, 0.505, 0.51, 1.0};
   float achievements_box_list_x = 0;
   float achievements_box_list_y = 0;
   float y_spacing = achievements_box_height + box_gutter_y;
   float frame_thickness = 6.0;
   float frame_outset = box_gutter_y + 2;
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   float normalized_scrollbar_position = scrollbar_position / container_scroll_range;

   AllegroFlare::Placement2D place(
      achievements_list_x,
      achievements_list_y,
      achievements_list_width,
      container_height
   );

   place.start_transform();

   // draw the items in the list
   for (int i=0; i<achievements.size(); i++)
   {
      std::string status = std::get<0>(achievements[i]);
      std::string title = std::get<1>(achievements[i]);
      std::string description = std::get<2>(achievements[i]);
      draw_achievement_box(
         achievements_box_list_x,
         achievements_box_list_y + i * y_spacing - scrollbar_position,
         status,
         title,
         description
      );
   }

   //// draw the frame
   //al_draw_rounded_rectangle(
   //   0 - frame_outset,
   //   0 - frame_outset,
   //   achievements_list_width + frame_outset,
   //   achievements_list_container_height + frame_outset,
   //   5.0,
   //   5.0,
   //   achievements_list_frame_color,
   //   frame_thickness
   //);

   // draw the scrollbar
   if (!scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container())
   {
      AllegroFlare::Elements::Scrollbar scrollbar(
         achievements_list_width + scrollbar_x_padding,
         scrollbar_y_padding,
         container_height - scrollbar_y_padding * 2,
         normalized_scrollbar_position,
         scrollbar_bar_color,
         scrollbar_handle_color
      );
      scrollbar.render();
   }

   place.restore_transform();
   return;
}

void AchievementsList::draw_achievement_box(float x, float y, std::string status, std::string title, std::string description)
{
   ALLEGRO_FONT *item_title_font = obtain_item_title_font();
   ALLEGRO_FONT *description_font = obtain_item_description_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   //float achievements_box_width = 800.0f;
   //float achievements_box_height = 150.0f;
   float box_padding_x = 20;
   float box_padding_y = 20;
   float title_padding_y = 10;
   ALLEGRO_COLOR title_text_color_normal = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR description_text_color = ALLEGRO_COLOR{0.7, 0.705, 0.71, 1.0};
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   ALLEGRO_COLOR icon_container_box_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR icon_locked_color = ALLEGRO_COLOR{0.4, 0.405, 0.41, 1};
   ALLEGRO_COLOR icon_hidden_color = icon_container_box_color;
   ALLEGRO_COLOR icon_achieved_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR title_text_color_hidden = icon_locked_color;
   float item_title_font_line_height = al_get_font_line_height(item_title_font);
   float description_font_line_height = al_get_font_line_height(description_font);
   float icon_font_line_height = al_get_font_line_height(icon_font);
   float icon_container_box_size = achievements_box_height - box_padding_x*2;
   float text_y_offset = 2;
   float icon_container_box_text_x_padding = 30;
   float text_x_offset = icon_container_box_size + icon_container_box_text_x_padding;

   ALLEGRO_COLOR title_text_color = (status == "hidden") ? title_text_color_hidden : title_text_color_normal;

   float icon_box_center_x = x + box_padding_x + icon_container_box_size / 2;
   float icon_box_center_y = y + box_padding_y + icon_container_box_size / 2;
   int32_t icon_character = infer_icon_character_by_status(status);
   ALLEGRO_COLOR icon_color = infer_icon_color_by_status(
      status,
      icon_locked_color,
      icon_hidden_color,
      icon_achieved_color
   );

   // draw the filled rectangle
   if (status == "hidden")
   {
      float hidden_box_stroke_thickness = 4.0f;
      float h_thickness = hidden_box_stroke_thickness * 0.5;
      al_draw_rectangle(
         x + h_thickness,
         y + h_thickness,
         x + achievements_box_width - h_thickness,
         y + achievements_box_height - h_thickness,
         box_color,
         hidden_box_stroke_thickness
      );
   }
   else
   {
      al_draw_filled_rectangle(x, y, x + achievements_box_width, y + achievements_box_height, box_color);
   }

   // draw the icon container box rectangle
   if (status == "hidden")
   {
      float hidden_icon_box_stroke_thickness = 4.0f;
      float h_thickness = hidden_icon_box_stroke_thickness * 0.5;
      al_draw_rectangle(
         x + box_padding_x + h_thickness,
         y + box_padding_y + h_thickness,
         x + box_padding_x + icon_container_box_size - h_thickness,
         y + box_padding_y + icon_container_box_size - h_thickness,
         icon_container_box_color,
         hidden_icon_box_stroke_thickness
      );
   }
   else
   {
      al_draw_filled_rectangle(
         x + box_padding_x,
         y + box_padding_y,
         x + box_padding_x + icon_container_box_size,
         y + box_padding_y + icon_container_box_size,
         icon_container_box_color
      );
   }

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
      item_title_font,
      title_text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + text_y_offset + 2,
      ALLEGRO_ALIGN_LEFT,
      filter_item_title_through_status(title, status).c_str()
   );

   // draw the description text
   al_draw_multiline_text(
      description_font,
      description_text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + item_title_font_line_height + title_padding_y + text_y_offset + 1,
      achievements_box_width - (box_padding_x + icon_container_box_size + icon_container_box_text_x_padding*2),
      description_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      filter_item_description_through_status(description, status).c_str()
   );

   return;
}

int32_t AchievementsList::infer_icon_character_by_status(std::string status)
{
   if (status == "unlocked") return 0xf091;
   else if (status == "locked") return 0xf023;
   else if (status == "hidden") return 0x3f;
   return 0xe1fe;
}

ALLEGRO_COLOR AchievementsList::infer_icon_color_by_status(std::string status, ALLEGRO_COLOR icon_locked_color, ALLEGRO_COLOR icon_hidden_color, ALLEGRO_COLOR icon_achieved_color)
{
   if (status == "unlocked") return icon_achieved_color;
   else if (status == "locked") return icon_locked_color;
   else if (status == "hidden") return icon_hidden_color;
   return ALLEGRO_COLOR{1, 0, 0, 1};
}

std::string AchievementsList::filter_item_title_through_status(std::string title, std::string status)
{
   if (status == "hidden") return "Hidden Achievement";
   return title;
}

std::string AchievementsList::filter_item_description_through_status(std::string description, std::string status)
{
   if (status == "hidden") return "";
   return description;
}

ALLEGRO_FONT* AchievementsList::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -40");
}

ALLEGRO_FONT* AchievementsList::obtain_item_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::obtain_item_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::obtain_item_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -34");
}

ALLEGRO_FONT* AchievementsList::obtain_item_description_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::obtain_item_description_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::obtain_item_description_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -26");
}

ALLEGRO_FONT* AchievementsList::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::AchievementsList::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::AchievementsList::obtain_icon_font]: error: guard \"font_bin\" not met");
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


