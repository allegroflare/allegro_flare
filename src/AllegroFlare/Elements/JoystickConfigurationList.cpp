

#include <AllegroFlare/Elements/JoystickConfigurationList.hpp>

#include <AllegroFlare/Elements/Scrollbar.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


JoystickConfigurationList::JoystickConfigurationList(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping, float list_item_box_width, float list_item_box_height)
   : font_bin(font_bin)
   , joystick_configuration_mapping(joystick_configuration_mapping)
   , list_item_box_width(list_item_box_width)
   , list_item_box_height(list_item_box_height)
   , surface_width(1920)
   , surface_height(1080)
   , scrollbar_position(0.0f)
   , box_gutter_y(10.0f)
{
}


JoystickConfigurationList::~JoystickConfigurationList()
{
}


void JoystickConfigurationList::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void JoystickConfigurationList::set_joystick_configuration_mapping(std::vector<std::tuple<std::string, uint32_t>> joystick_configuration_mapping)
{
   this->joystick_configuration_mapping = joystick_configuration_mapping;
}


void JoystickConfigurationList::set_list_item_box_width(float list_item_box_width)
{
   this->list_item_box_width = list_item_box_width;
}


void JoystickConfigurationList::set_list_item_box_height(float list_item_box_height)
{
   this->list_item_box_height = list_item_box_height;
}


void JoystickConfigurationList::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void JoystickConfigurationList::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


void JoystickConfigurationList::set_box_gutter_y(float box_gutter_y)
{
   this->box_gutter_y = box_gutter_y;
}


std::vector<std::tuple<std::string, uint32_t>> JoystickConfigurationList::get_joystick_configuration_mapping() const
{
   return joystick_configuration_mapping;
}


float JoystickConfigurationList::get_list_item_box_width() const
{
   return list_item_box_width;
}


float JoystickConfigurationList::get_list_item_box_height() const
{
   return list_item_box_height;
}


int JoystickConfigurationList::get_surface_width() const
{
   return surface_width;
}


int JoystickConfigurationList::get_surface_height() const
{
   return surface_height;
}


float JoystickConfigurationList::get_scrollbar_position() const
{
   return scrollbar_position;
}


float JoystickConfigurationList::get_box_gutter_y() const
{
   return box_gutter_y;
}


void JoystickConfigurationList::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_joystick_configuration_mapping_list_items_and_scrollbar();
   draw_joystick_configuration_mapping_list_title_text();
   return;
}

void JoystickConfigurationList::move_scrollbar_position(float distance_y)
{
   scrollbar_position += distance_y;
   limit_scrollbar_position();
   return;
}

void JoystickConfigurationList::set_scrollbar_position(float scrollbar_position)
{
   this->scrollbar_position = scrollbar_position;
   limit_scrollbar_position();
   return;
}

void JoystickConfigurationList::set_scrollbar_position_to_max()
{
   this->scrollbar_position = infer_container_scroll_range();
   return;
}

float JoystickConfigurationList::infer_scrollbar_max_position()
{
   return infer_container_scroll_range();
}

bool JoystickConfigurationList::scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container()
{
   return infer_container_scroll_range() <= 0;
}

std::vector<std::tuple<std::string, uint32_t>> JoystickConfigurationList::build_placeholder_joystick_configuration_mapping()
{
   return {
      { "Primary Action", 1 },
      { "Secondary Action", 2 },
      { "Back", 3 },
      { "Up", 4 },
      { "Down", 5 },
      { "Left", 6 },
      { "Right", 7 },
      //{ "unlocked", "Fade In", "Start out in the world." },
      //{ "locked",   "Call to Adventure", "Leave what you know in order to take on a challenge you must face." },
      //{ "locked",   "Save the Cat", "Define the hero and make the audience like them." },
      //{ "unlocked", "Break the Fourth Wall", "Make the developer realize they're looking at test data." },
      //{ "hidden",   "Top Secrets", "Find the box of secrets in the 2nd act." },
      //{ "locked",   "I'm Lovin' It", "Complete the AchievementsList feature." },
      //{ "unlocked", "Everyone is Beautiful", "Make multiline text fit into the box with the correct width." },
      //{ "hidden",   "Save the Best for Last", "Find out the most important part in the very end." },
   };
}

void JoystickConfigurationList::draw_header_title_backfill()
{
   // draw inputs
   float backfill_opacity = 0.35;
   float bar_height = 160;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, backfill_opacity};
   al_draw_filled_rectangle(0, 0, surface_width, bar_height, backfill_color);
   return;
}

int JoystickConfigurationList::count_num_joystick_configuration_mapping()
{
   return joystick_configuration_mapping.size();
}

void JoystickConfigurationList::draw_joystick_configuration_mapping_list_title_text()
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
      "Joystick Configuration (Generic)"
      //"J O Y S T I C K   C O N F I G U R A T I O N"
   );

   //// draw the number achieved
   //al_draw_text(
      //font,
      //color,
      //1920-surface_padding_x,
      //100,
      //ALLEGRO_ALIGN_RIGHT,
      //build_joystick_configuration_mapping_count_string().c_str()
   //);

   return;
}

float JoystickConfigurationList::infer_container_height()
{
   return 800;
   //return (list_item_box_height + box_gutter_y) * 5.5;
}

float JoystickConfigurationList::infer_container_contents_height()
{
   float y_spacing = list_item_box_height + box_gutter_y;
   return joystick_configuration_mapping.size() * y_spacing - box_gutter_y; // <- this should be revised
                                                          // to take into account
                                                          // lists of size 0; E.g.
                                                          // Box gutter y should not
                                                          // be subtracted in that
                                                          // case
}

float JoystickConfigurationList::infer_container_scroll_range()
{
   return infer_container_contents_height() - infer_container_height();
}

void JoystickConfigurationList::limit_scrollbar_position()
{
   float y_spacing = list_item_box_height + box_gutter_y;
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   scrollbar_position = std::max(0.0f, std::min(container_scroll_range, scrollbar_position));
   return;
}

void JoystickConfigurationList::draw_joystick_configuration_mapping_list_items_and_scrollbar()
{
   float joystick_configuration_mapping_list_x = surface_width/2;
   float joystick_configuration_mapping_list_y = surface_height/2 + 40;
   float joystick_configuration_mapping_list_width = list_item_box_width;
   float scrollbar_x_padding = 70;
   float scrollbar_y_padding = 26;
   ALLEGRO_COLOR joystick_configuration_mapping_list_frame_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_bar_color = ALLEGRO_COLOR{0.2, 0.205, 0.21, 1.0};
   ALLEGRO_COLOR scrollbar_handle_color = ALLEGRO_COLOR{0.5, 0.505, 0.51, 1.0};
   float joystick_configuration_mapping_box_list_x = 0;
   float joystick_configuration_mapping_box_list_y = 0;
   float y_spacing = list_item_box_height + box_gutter_y;
   float frame_thickness = 6.0;
   float frame_outset = box_gutter_y + 2;
   float container_height = infer_container_height();
   float container_contents_height = infer_container_contents_height();
   float container_scroll_range = infer_container_scroll_range();
   float normalized_scrollbar_position = scrollbar_position / container_scroll_range;

   AllegroFlare::Placement2D place(
      joystick_configuration_mapping_list_x,
      joystick_configuration_mapping_list_y,
      joystick_configuration_mapping_list_width,
      container_height
   );

   place.start_transform();

   // draw the items in the list
   for (int i=0; i<joystick_configuration_mapping.size(); i++)
   {
      std::string action_label = std::get<0>(joystick_configuration_mapping[i]);
      uint32_t mapped_button_num = std::get<1>(joystick_configuration_mapping[i]);
      //std::string description = std::get<2>(joystick_configuration_mapping[i]);
      // TODO:
      // HERE: render
      draw_joystick_configuration_item_box(
         joystick_configuration_mapping_box_list_x,
         joystick_configuration_mapping_box_list_y + i * y_spacing - scrollbar_position,
         action_label,
         "Button " + std::to_string(mapped_button_num)
      );

      //draw_achievement_box(
         //joystick_configuration_mapping_box_list_x,
         //joystick_configuration_mapping_box_list_y + i * y_spacing - scrollbar_position,
         //status,
         //title,
         //description
      //);
   }

   //// draw the frame
   //al_draw_rounded_rectangle(
   //   0 - frame_outset,
   //   0 - frame_outset,
   //   joystick_configuration_mapping_list_width + frame_outset,
   //   joystick_configuration_mapping_list_container_height + frame_outset,
   //   5.0,
   //   5.0,
   //   joystick_configuration_mapping_list_frame_color,
   //   frame_thickness
   //);

   // draw the scrollbar
   if (!scrollbar_is_autohidden_because_list_contents_is_smaller_than_the_container())
   {
      AllegroFlare::Elements::Scrollbar scrollbar(
         joystick_configuration_mapping_list_width + scrollbar_x_padding,
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

void JoystickConfigurationList::draw_joystick_configuration_item_box(float x, float y, std::string action_name, std::string mapped_button_name)
{
   ALLEGRO_COLOR box_color = ALLEGRO_COLOR{0.1, 0.105, 0.11, 1.0};
   ALLEGRO_FONT *item_title_font = obtain_item_title_font();
   float box_padding_x = 26;
   float box_padding_y = 10;
   int text_y = (list_item_box_height / 2) - (al_get_font_line_height(item_title_font) / 2);

   // draw the backfill box
   al_draw_filled_rectangle(x, y, x + list_item_box_width, y + list_item_box_height, box_color);

   // draw the action_name
   al_draw_text(
      item_title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      x + box_padding_x,
      y + text_y, // update this to be vertical-centered
      ALLEGRO_ALIGN_LEFT,
      action_name.c_str()
   );

   // draw the mapped_button_name
   // draw the mapped_button_name background box
   float column_2_x = 550;
   float mapped_button_background_box_width = 160;
   float mapped_button_background_box_height = list_item_box_height - box_padding_y*2;
   float mapped_button_name_x = x + list_item_box_width - mapped_button_background_box_width - box_padding_x;
   float mapped_button_name_y = text_y;

   al_draw_filled_rectangle(
      mapped_button_name_x - mapped_button_background_box_width,
      y + box_padding_y,
      mapped_button_name_x + mapped_button_background_box_width,
      y + box_padding_y + mapped_button_background_box_height,
      ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}
   );

   // draw the mapped_button_name text
   al_draw_text(
      item_title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      mapped_button_name_x,
      y + mapped_button_name_y,
      ALLEGRO_ALIGN_CENTER,
      mapped_button_name.c_str()
   );
   return;
}

int32_t JoystickConfigurationList::infer_icon_character_by_status(std::string status)
{
   if (status == "unlocked") return 0xf091;
   else if (status == "locked") return 0xf023;
   else if (status == "hidden") return 0x3f;
   return 0xe1fe;
}

ALLEGRO_COLOR JoystickConfigurationList::infer_icon_color_by_status(std::string status, ALLEGRO_COLOR icon_locked_color, ALLEGRO_COLOR icon_hidden_color, ALLEGRO_COLOR icon_achieved_color)
{
   if (status == "unlocked") return icon_achieved_color;
   else if (status == "locked") return icon_locked_color;
   else if (status == "hidden") return icon_hidden_color;
   return ALLEGRO_COLOR{1, 0, 0, 1};
}

std::string JoystickConfigurationList::filter_item_title_through_status(std::string title, std::string status)
{
   if (status == "hidden") return "Hidden Achievement";
   return title;
}

std::string JoystickConfigurationList::filter_item_description_through_status(std::string description, std::string status)
{
   if (status == "hidden") return "";
   return description;
}

ALLEGRO_FONT* JoystickConfigurationList::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::obtain_title_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -40");
}

ALLEGRO_FONT* JoystickConfigurationList::obtain_item_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::obtain_item_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::obtain_item_title_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -34");
}

ALLEGRO_FONT* JoystickConfigurationList::obtain_item_description_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::obtain_item_description_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::obtain_item_description_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -26");
}

ALLEGRO_FONT* JoystickConfigurationList::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfigurationList::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfigurationList::obtain_icon_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("fa-solid-900.ttf -50");
}

void JoystickConfigurationList::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}


} // namespace Elements
} // namespace AllegroFlare


