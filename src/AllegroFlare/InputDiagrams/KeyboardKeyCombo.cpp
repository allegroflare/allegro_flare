

#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/InputDiagrams/KeyboardKey.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace InputDiagrams
{


KeyboardKeyCombo::KeyboardKeyCombo(AllegroFlare::FontBin* font_bin, std::vector<std::string> keyboard_combo_tokens, ALLEGRO_COLOR color)
   : font_bin(font_bin)
   , keyboard_combo_tokens(keyboard_combo_tokens)
   , color(color)
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


AllegroFlare::FontBin* KeyboardKeyCombo::get_font_bin()
{
   return font_bin;
}


std::vector<std::string> KeyboardKeyCombo::get_keyboard_combo_tokens()
{
   return keyboard_combo_tokens;
}


ALLEGRO_COLOR KeyboardKeyCombo::get_color()
{
   return color;
}


float KeyboardKeyCombo::get_keyboard_key_box_height()
{
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key;
   return keyboard_key.get_keyboard_key_box_height();
}

void KeyboardKeyCombo::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   AllegroFlare::InputDiagrams::KeyboardKey keyboard_key(font_bin);
   float box_height = get_keyboard_key_box_height();
   float token_space_width = 10;
   float token_big_space_width = 14;
   float token_separator_width = 60;
   bool next_token_is_raw_text = false;

   float cursor_x = 0;
   for (auto &keyboard_combo_token : keyboard_combo_tokens)
   {
      if (next_token_is_raw_text)
      {
         next_token_is_raw_text = false;

         ALLEGRO_FONT *font = obtain_font();
         float font_ascent_height = al_get_font_line_height(font);
         al_draw_text(
            font,
            color,
            (int)(cursor_x),
            (int)(box_height/ 2 - font_ascent_height / 2),
            ALLEGRO_ALIGN_LEFT,
            keyboard_combo_token.c_str()
         );

         cursor_x += al_get_text_width(font, keyboard_combo_token.c_str());
      }
      else if (keyboard_combo_token == "%SPACE")
      {
         cursor_x += token_space_width;
      }
      else if (keyboard_combo_token == "%BIGSPACE")
      {
         cursor_x += token_big_space_width;
      }
      else if (keyboard_combo_token == "%SPACER")
      {
         cursor_x += (token_big_space_width + token_space_width);
      }
      else if (keyboard_combo_token == "%SEPARATOR")
      {
         cursor_x += token_separator_width;
      }
      else if (keyboard_combo_token == "LABEL>>")
      {
         next_token_is_raw_text = true;
      }
      else if (keyboard_combo_token == "%PLUS")
      {
         ALLEGRO_FONT *font = obtain_font();
         float font_ascent_height = al_get_font_line_height(font);
         al_draw_text(
            font,
            color,
            (int)(cursor_x),
            (int)(box_height/ 2 - font_ascent_height / 2),
            ALLEGRO_ALIGN_CENTER,
            "+"
         );
      }
      else if (keyboard_combo_token == "%SLASH")
      {
         ALLEGRO_FONT *font = obtain_font();
         float font_ascent_height = al_get_font_line_height(font);
         al_draw_text(
            font,
            color,
            (int)(cursor_x),
            (int)(box_height/ 2 - font_ascent_height / 2),
            ALLEGRO_ALIGN_CENTER,
            "/"
         );
      }
      else // is a regular interpreted-as-text token
      {
         keyboard_key.set_keyboard_key_str(keyboard_combo_token);
         keyboard_key.set_x(cursor_x);
         //keyboard_key.set_x = 
         float key_width = keyboard_key.render();
         cursor_x += key_width;
      }
   }
   return;
}

ALLEGRO_FONT* KeyboardKeyCombo::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "KeyboardKeyCombo" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string font_name = "Inter-Medium.ttf";
   int font_size = -28;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace InputDiagrams
} // namespace AllegroFlare


