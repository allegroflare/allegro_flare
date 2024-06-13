

#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace InputDiagrams
{


KeyboardKey::KeyboardKey(AllegroFlare::FontBin* font_bin, std::string keyboard_key_str, ALLEGRO_COLOR color, float x, float y, float keyboard_key_box_height, float keyboard_key_box_min_width, std::string font_name, int font_size)
   : font_bin(font_bin)
   , keyboard_key_str(keyboard_key_str)
   , color(color)
   , x(x)
   , y(y)
   , keyboard_key_box_height(keyboard_key_box_height)
   , keyboard_key_box_min_width(keyboard_key_box_min_width)
   , font_name(font_name)
   , font_size(font_size)
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


void KeyboardKey::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void KeyboardKey::set_font_size(int font_size)
{
   this->font_size = font_size;
}


AllegroFlare::FontBin* KeyboardKey::get_font_bin() const
{
   return font_bin;
}


std::string KeyboardKey::get_keyboard_key_str() const
{
   return keyboard_key_str;
}


ALLEGRO_COLOR KeyboardKey::get_color() const
{
   return color;
}


float KeyboardKey::get_x() const
{
   return x;
}


float KeyboardKey::get_y() const
{
   return y;
}


float KeyboardKey::get_keyboard_key_box_height() const
{
   return keyboard_key_box_height;
}


float KeyboardKey::get_keyboard_key_box_min_width() const
{
   return keyboard_key_box_min_width;
}


std::string KeyboardKey::get_font_name() const
{
   return font_name;
}


int KeyboardKey::get_font_size() const
{
   return font_size;
}


void KeyboardKey::set_keyboard_key_box_height(float keyboard_key_box_height)
{
   this->keyboard_key_box_height = keyboard_key_box_height;
   this->keyboard_key_box_min_width = keyboard_key_box_height;
   return;
}

int KeyboardKey::render(bool calculate_width_only_and_do_not_draw)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKey::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   float padding_x = 12;
   float text_width = al_get_text_width(font, keyboard_key_str.c_str());
   float box_width = guarantee_even_number(std::max(keyboard_key_box_min_width, text_width + padding_x*2));
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

int KeyboardKey::calculate_width()
{
   return render(true);
}

int KeyboardKey::guarantee_even_number(int potentially_odd_number)
{
   if (potentially_odd_number % 2 == 1) return potentially_odd_number + 1;
   return potentially_odd_number;
}

ALLEGRO_FONT* KeyboardKey::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKey::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKey::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace InputDiagrams
} // namespace AllegroFlare


