

#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace InputDiagrams
{


KeyboardKey::KeyboardKey(AllegroFlare::FontBin* font_bin, std::string keyboard_key_str, ALLEGRO_COLOR color, float x, float y, float keyboard_key_box_height, float keyboard_key_box_min_width)
   : font_bin(font_bin)
   , keyboard_key_str(keyboard_key_str)
   , color(color)
   , x(x)
   , y(y)
   , keyboard_key_box_height(keyboard_key_box_height)
   , keyboard_key_box_min_width(keyboard_key_box_min_width)
{
}


KeyboardKey::~KeyboardKey()
{
}


void KeyboardKey::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void KeyboardKey::set_keyboard_key_str(std::string keyboard_key_str)
{
   this->keyboard_key_str = keyboard_key_str;
}


void KeyboardKey::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


void KeyboardKey::set_x(float x)
{
   this->x = x;
}


void KeyboardKey::set_y(float y)
{
   this->y = y;
}


void KeyboardKey::set_keyboard_key_box_height(float keyboard_key_box_height)
{
   this->keyboard_key_box_height = keyboard_key_box_height;
}


void KeyboardKey::set_keyboard_key_box_min_width(float keyboard_key_box_min_width)
{
   this->keyboard_key_box_min_width = keyboard_key_box_min_width;
}


AllegroFlare::FontBin* KeyboardKey::get_font_bin()
{
   return font_bin;
}


std::string KeyboardKey::get_keyboard_key_str()
{
   return keyboard_key_str;
}


ALLEGRO_COLOR KeyboardKey::get_color()
{
   return color;
}


float KeyboardKey::get_x()
{
   return x;
}


float KeyboardKey::get_y()
{
   return y;
}


float KeyboardKey::get_keyboard_key_box_height()
{
   return keyboard_key_box_height;
}


float KeyboardKey::get_keyboard_key_box_min_width()
{
   return keyboard_key_box_min_width;
}


float KeyboardKey::render(bool calculate_width_only_and_do_not_draw)
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *font = obtain_font();
   float padding_x = 12;
   float text_width = al_get_text_width(font, keyboard_key_str.c_str());
   float box_width = std::max(keyboard_key_box_min_width, text_width + padding_x*2);
   if (calculate_width_only_and_do_not_draw) return box_width;
   float roundness = 4;
   float line_thickness = 1.5;
   float font_ascent_height = al_get_font_line_height(font);

   al_draw_rounded_rectangle(
      x + 0,
      y + 0,
      x + box_width,
      y + get_keyboard_key_box_height(),
      roundness,
      roundness,
      color,
      line_thickness
   );
   al_draw_text(
      font,
      color,
      (int)(x + box_width / 2),
      (int)(y + keyboard_key_box_height / 2 - font_ascent_height / 2),
      ALLEGRO_ALIGN_CENTER,
      keyboard_key_str.c_str()
   );

   return box_width;
}

float KeyboardKey::calculate_width()
{
   return render(true);
}

ALLEGRO_FONT* KeyboardKey::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "KeyboardKey" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_name = "Inter-Medium.ttf";
   int font_size = -20;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace InputDiagrams
} // namespace AllegroFlare


