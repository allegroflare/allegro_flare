

#include <AllegroFlare/Elements/NotificationRenderers/JoystickConnected.hpp>

#include <AllegroFlare/MotionFX/Sparkles2.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace NotificationRenderers
{


JoystickConnected::JoystickConnected(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, float x, float y, float width, float height, float created_at, std::string name)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , x(x)
   , y(y)
   , width(width)
   , height(height)
   , created_at(created_at)
   , name(name)
{
}


JoystickConnected::~JoystickConnected()
{
}


void JoystickConnected::set_x(float x)
{
   this->x = x;
}


void JoystickConnected::set_y(float y)
{
   this->y = y;
}


void JoystickConnected::set_width(float width)
{
   this->width = width;
}


void JoystickConnected::set_height(float height)
{
   this->height = height;
}


void JoystickConnected::set_created_at(float created_at)
{
   this->created_at = created_at;
}


void JoystickConnected::set_name(std::string name)
{
   this->name = name;
}


float JoystickConnected::get_x() const
{
   return x;
}


float JoystickConnected::get_y() const
{
   return y;
}


float JoystickConnected::get_width() const
{
   return width;
}


float JoystickConnected::get_height() const
{
   return height;
}


float JoystickConnected::get_created_at() const
{
   return created_at;
}


std::string JoystickConnected::get_name() const
{
   return name;
}


void JoystickConnected::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_achievement_box("Joystick Connected", name);
   return;
}

void JoystickConnected::draw_achievement_box(std::string title, std::string description)
{
   std::string status = "unlocked";
   ALLEGRO_FONT *item_title_font = obtain_item_title_font();
   ALLEGRO_FONT *description_font = obtain_item_description_font();
   ALLEGRO_FONT *icon_font = obtain_icon_font();
   float achievements_box_width = width; //560.0f;
   float achievements_box_height = height; //130.0f;
   float box_padding_x = 16;
   float box_padding_y = 16;
   float title_to_description_gutter = 6;
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
   float text_y_offset = 14;
   float icon_container_box_text_x_padding = 30;
   float text_x_offset = icon_container_box_size + icon_container_box_text_x_padding;

   ALLEGRO_COLOR title_text_color = (status == "hidden") ? title_text_color_hidden : title_text_color_normal;

   float icon_box_center_x = x + box_padding_x + icon_container_box_size / 2;
   float icon_box_center_y = y + box_padding_y + icon_container_box_size / 2;
   int32_t icon_character = infer_icon_character_by_status(status);
   ALLEGRO_COLOR icon_color = ALLEGRO_COLOR{1, 1, 1, 1}; //infer_icon_color_by_status(
      //status,
      //icon_locked_color,
      //icon_hidden_color,
      //icon_achieved_color
   //);

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
      y + box_padding_y + text_y_offset,
      ALLEGRO_ALIGN_LEFT,
      title.c_str()
   );

   // draw the description text
   al_draw_multiline_text(
      description_font,
      description_text_color,
      x + box_padding_x + text_x_offset,
      y + box_padding_y + item_title_font_line_height + title_to_description_gutter + text_y_offset,
      achievements_box_width - (box_padding_x + icon_container_box_size + icon_container_box_text_x_padding*2),
      description_font_line_height,
      ALLEGRO_ALIGN_LEFT,
      description.c_str()
   );

   // draw the sparkle effect
   //AllegroFlare::MotionFX::Sparkles2 sparkles2(bitmap_bin, icon_box_center_x, icon_box_center_y-2);
   //sparkles2.set_scale(0.32);
   //sparkles2.initialize();
   //sparkles2.set_time(al_get_time() - created_at);
   //sparkles2.render();

   return;
}

int32_t JoystickConnected::infer_icon_character_by_status(std::string status)
{
   return 0xf11b;
   //if (status == "unlocked") return 0xf091;
   //else if (status == "locked") return 0xf023;
   //else if (status == "hidden") return 0x3f;
   //return 0xe1fe;
}

ALLEGRO_COLOR JoystickConnected::infer_icon_color_by_status(std::string status, ALLEGRO_COLOR icon_locked_color, ALLEGRO_COLOR icon_hidden_color, ALLEGRO_COLOR icon_achieved_color)
{
   if (status == "unlocked") return icon_achieved_color;
   else if (status == "locked") return icon_locked_color;
   else if (status == "hidden") return icon_hidden_color;
   return ALLEGRO_COLOR{1, 0, 0, 1};
}

ALLEGRO_FONT* JoystickConnected::obtain_item_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_item_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_item_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}

ALLEGRO_FONT* JoystickConnected::obtain_item_description_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_item_description_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_item_description_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -26");
}

ALLEGRO_FONT* JoystickConnected::obtain_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::NotificationRenderers::JoystickConnected::obtain_icon_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("fa-solid-900.ttf -50");
}

void JoystickConnected::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int x, int y, uint32_t icon, int flags)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}


} // namespace NotificationRenderers
} // namespace Elements
} // namespace AllegroFlare


