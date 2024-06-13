

#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>

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


KeyboardKeyCombo::KeyboardKeyCombo(AllegroFlare::FontBin* font_bin, std::vector<std::string> keyboard_combo_tokens, ALLEGRO_COLOR color, float x, float y, std::string font_name, int font_size, std::string keyboard_key_font_name, int keyboard_key_font_size, float keyboard_key_box_height, float keyboard_key_box_min_width, float token_SPACE_width, float token_SPACER_width, float token_SEPARATOR_width)
   : font_bin(font_bin)
   , keyboard_combo_tokens(keyboard_combo_tokens)
   , color(color)
   , x(x)
   , y(y)
   , font_name(font_name)
   , font_size(font_size)
   , keyboard_key_font_name(keyboard_key_font_name)
   , keyboard_key_font_size(keyboard_key_font_size)
   , keyboard_key_box_height(keyboard_key_box_height)
   , keyboard_key_box_min_width(keyboard_key_box_min_width)
   , token_SPACE_width(token_SPACE_width)
   , token_SPACER_width(token_SPACER_width)
   , token_SEPARATOR_width(token_SEPARATOR_width)
{
}


KeyboardKeyCombo::~KeyboardKeyCombo()
{
}


void KeyboardKeyCombo::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void KeyboardKeyCombo::set_keyboard_combo_tokens(std::vector<std::string> keyboard_combo_tokens)
{
   this->keyboard_combo_tokens = keyboard_combo_tokens;
}


void KeyboardKeyCombo::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


void KeyboardKeyCombo::set_x(float x)
{
   this->x = x;
}


void KeyboardKeyCombo::set_y(float y)
{
   this->y = y;
}


void KeyboardKeyCombo::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void KeyboardKeyCombo::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void KeyboardKeyCombo::set_keyboard_key_font_name(std::string keyboard_key_font_name)
{
   this->keyboard_key_font_name = keyboard_key_font_name;
}


void KeyboardKeyCombo::set_keyboard_key_font_size(int keyboard_key_font_size)
{
   this->keyboard_key_font_size = keyboard_key_font_size;
}


void KeyboardKeyCombo::set_token_SPACE_width(float token_SPACE_width)
{
   this->token_SPACE_width = token_SPACE_width;
}


void KeyboardKeyCombo::set_token_SPACER_width(float token_SPACER_width)
{
   this->token_SPACER_width = token_SPACER_width;
}


void KeyboardKeyCombo::set_token_SEPARATOR_width(float token_SEPARATOR_width)
{
   this->token_SEPARATOR_width = token_SEPARATOR_width;
}


AllegroFlare::FontBin* KeyboardKeyCombo::get_font_bin() const
{
   return font_bin;
}


std::vector<std::string> KeyboardKeyCombo::get_keyboard_combo_tokens() const
{
   return keyboard_combo_tokens;
}


ALLEGRO_COLOR KeyboardKeyCombo::get_color() const
{
   return color;
}


float KeyboardKeyCombo::get_x() const
{
   return x;
}


float KeyboardKeyCombo::get_y() const
{
   return y;
}


std::string KeyboardKeyCombo::get_font_name() const
{
   return font_name;
}


int KeyboardKeyCombo::get_font_size() const
{
   return font_size;
}


std::string KeyboardKeyCombo::get_keyboard_key_font_name() const
{
   return keyboard_key_font_name;
}


int KeyboardKeyCombo::get_keyboard_key_font_size() const
{
   return keyboard_key_font_size;
}


float KeyboardKeyCombo::get_keyboard_key_box_height() const
{
   return keyboard_key_box_height;
}


float KeyboardKeyCombo::get_keyboard_key_box_min_width() const
{
   return keyboard_key_box_min_width;
}


float KeyboardKeyCombo::get_token_SPACE_width() const
{
   return token_SPACE_width;
}


float KeyboardKeyCombo::get_token_SPACER_width() const
{
   return token_SPACER_width;
}


float KeyboardKeyCombo::get_token_SEPARATOR_width() const
{
   return token_SEPARATOR_width;
}


void KeyboardKeyCombo::set_keyboard_key_box_height(float keyboard_key_box_height)
{
   this->keyboard_key_box_height = keyboard_key_box_height;
   this->keyboard_key_box_min_width = keyboard_key_box_height;
   return;
}

int KeyboardKeyCombo::render(bool calculate_width_only_and_do_not_draw)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKeyCombo::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(font_bin);
   bool next_token_is_raw_text = false;
   bool do_actually_draw = !calculate_width_only_and_do_not_draw;

   int cursor_x = 0;
   for (auto &keyboard_combo_token : keyboard_combo_tokens)
   {
      if (next_token_is_raw_text)
      {
         next_token_is_raw_text = false;

         ALLEGRO_FONT *font = obtain_font();
         if (do_actually_draw)
         {
            float font_ascent_height = al_get_font_line_height(font);
            al_draw_text(
               font,
               color,
               (int)(x + cursor_x),
               (int)(y + keyboard_key_box_height/ 2 - font_ascent_height / 2),
               ALLEGRO_ALIGN_LEFT,
               keyboard_combo_token.c_str()
            );
         }

         cursor_x += al_get_text_width(font, keyboard_combo_token.c_str());
      }
      else if (keyboard_combo_token == "%SPACE")
      {
         cursor_x += token_SPACE_width;
      }
      else if (keyboard_combo_token == "%SPACER")
      {
         cursor_x += token_SPACER_width;
      }
      else if (keyboard_combo_token == "%SEPARATOR")
      {
         cursor_x += token_SEPARATOR_width;
      }
      else if (keyboard_combo_token == "LABEL>>")
      {
         next_token_is_raw_text = true;
      }
      else if (keyboard_combo_token == "%PLUS")
      {
         ALLEGRO_FONT *font = obtain_font();
         if (do_actually_draw)
         {
            float font_ascent_height = al_get_font_line_height(font);
            al_draw_text(
               font,
               color,
               (int)(x + cursor_x),
               (int)(y + keyboard_key_box_height/ 2 - font_ascent_height / 2),
               ALLEGRO_ALIGN_LEFT,
               "+"
            );
         }

         cursor_x += al_get_text_width(font, "+");
      }
      else if (keyboard_combo_token == "%SLASH")
      {
         ALLEGRO_FONT *font = obtain_font();

         if (do_actually_draw)
         {
            float font_ascent_height = al_get_font_line_height(font);
            al_draw_text(
               font,
               color,
               (int)(x + cursor_x),
               (int)(y + keyboard_key_box_height/ 2 - font_ascent_height / 2),
               ALLEGRO_ALIGN_LEFT,
               "/"
            );
         }

         cursor_x += al_get_text_width(font, "/");
      }
      else // is a regular interpreted-as-text token
      {
         keyboard_key.set_keyboard_key_str(keyboard_combo_token);
         keyboard_key.set_x(x + cursor_x);
         keyboard_key.set_y(y);
         keyboard_key.set_color(color);
         keyboard_key.set_font_name(keyboard_key_font_name);
         keyboard_key.set_font_size(keyboard_key_font_size);
         keyboard_key.set_keyboard_key_box_height(keyboard_key_box_height);
         //keyboard_key.set_x = 
         float key_width = 0;
         key_width = keyboard_key.render(calculate_width_only_and_do_not_draw);
         cursor_x += key_width;
      }
   }

   return guarantee_even_number(cursor_x);
}

int KeyboardKeyCombo::calculate_width()
{
   return render(true);
}

int KeyboardKeyCombo::guarantee_even_number(int potentially_odd_number)
{
   if (potentially_odd_number % 2 == 1) return potentially_odd_number + 1;
   return potentially_odd_number;
}

ALLEGRO_FONT* KeyboardKeyCombo::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputDiagrams::KeyboardKeyCombo::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputDiagrams::KeyboardKeyCombo::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace InputDiagrams
} // namespace AllegroFlare


