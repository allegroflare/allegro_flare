

#include <AllegroFlare/InputHints.hpp>

#include <AllegroFlare/InputDiagrams/KeyboardKeyCombo.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


InputHints::InputHints(AllegroFlare::FontBin* font_bin, std::vector<std::pair<std::string, std::string>> input_hints_tokens, std::vector<std::string> keyboard_key_combo_tokens)
   : font_bin(font_bin)
   , input_hints_tokens(input_hints_tokens)
   , keyboard_key_combo_tokens(keyboard_key_combo_tokens)
   , bar_height(60)
   , text_color(ALLEGRO_COLOR{0.4, 0.4, 0.45, 0.6})
   , backfill_color(ALLEGRO_COLOR{0, 0, 0, 0.35})
   , surface_width(1920)
   , surface_height(1080)
{
}


InputHints::~InputHints()
{
}


void InputHints::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void InputHints::set_input_hints_tokens(std::vector<std::pair<std::string, std::string>> input_hints_tokens)
{
   this->input_hints_tokens = input_hints_tokens;
}


void InputHints::set_keyboard_key_combo_tokens(std::vector<std::string> keyboard_key_combo_tokens)
{
   this->keyboard_key_combo_tokens = keyboard_key_combo_tokens;
}


void InputHints::set_bar_height(int bar_height)
{
   this->bar_height = bar_height;
}


void InputHints::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void InputHints::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void InputHints::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void InputHints::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


AllegroFlare::FontBin* InputHints::get_font_bin() const
{
   return font_bin;
}


std::vector<std::pair<std::string, std::string>> InputHints::get_input_hints_tokens() const
{
   return input_hints_tokens;
}


std::vector<std::string> InputHints::get_keyboard_key_combo_tokens() const
{
   return keyboard_key_combo_tokens;
}


int InputHints::get_bar_height() const
{
   return bar_height;
}


ALLEGRO_COLOR InputHints::get_text_color() const
{
   return text_color;
}


ALLEGRO_COLOR InputHints::get_backfill_color() const
{
   return backfill_color;
}


int InputHints::get_surface_width() const
{
   return surface_width;
}


int InputHints::get_surface_height() const
{
   return surface_height;
}


void InputHints::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputHints::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputHints::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputHints::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputHints::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputHints::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputHints::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputHints::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputHints::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   draw_backfill_bar();
   if (!keyboard_key_combo_tokens.empty()) draw_keyboard_key_combo_tokens();
   else draw_inputs_hints_tokens();
   return;
}

void InputHints::draw_backfill_bar()
{
   if (backfill_color.a <= 0.0001) return;
   al_draw_filled_rectangle(0, surface_height-bar_height, surface_width, surface_height, backfill_color);
   return;
}

void InputHints::draw_keyboard_key_combo_tokens()
{
   AllegroFlare::InputDiagrams::KeyboardKeyCombo keyboard_key_combo(font_bin, keyboard_key_combo_tokens);
   float box_height = 30;
   keyboard_key_combo.set_keyboard_key_box_height(box_height);
   keyboard_key_combo.set_token_SPACE_width(6);
   keyboard_key_combo.set_token_SPACER_width(16);
   keyboard_key_combo.set_token_SEPARATOR_width(60);
   keyboard_key_combo.set_keyboard_key_font_size(-14);
   keyboard_key_combo.set_font_size(-18);
   keyboard_key_combo.set_color(text_color);

   float width = keyboard_key_combo.calculate_width();

   keyboard_key_combo.set_x(surface_width/2 - (width)/2);
   keyboard_key_combo.set_y((int)(surface_height - bar_height/2 - box_height/2));
   keyboard_key_combo.render();
   return;
}

void InputHints::draw_inputs_hints_tokens()
{
   // draw inputs text
   ALLEGRO_FONT *font = obtain_font();
   std::string SPACER = "         ";

   std::stringstream inputs_composite_str;
   for (int i=0; i<input_hints_tokens.size(); i++)
   {
      auto &input_hint = input_hints_tokens[i];
      std::string input_hint_key = input_hint.first;
      std::string input_hint_description = input_hint.second;
      bool is_last_input_hint = (i == input_hints_tokens.size()-1);

      inputs_composite_str << input_hint_key << "  " << input_hint_description;
      if (!is_last_input_hint) inputs_composite_str << SPACER;
   }

   float text_height = al_get_font_line_height(font);
   al_draw_text(
      font,
      text_color,
      surface_width/2,
      (int)(surface_height-text_height/2-bar_height/2),
      ALLEGRO_ALIGN_CENTER,
      inputs_composite_str.str().c_str()
   );
   return;
}

std::vector<std::pair<std::string, std::string>> InputHints::build_placeholder_input_hints_tokens()
{
   return std::vector<std::pair<std::string, std::string>>{
      { "[W/A/S/D]", "Move cursor" },
      { "[N/P]",     "Next/Previous entity" },
      { "[Shift+8]", "Capture screenshot" },
      { "[PAD +/-]", "Zoom" },
      { "[ESC]",     "Toggle Inventory" },
      { "[-/+]",     "Change time of day" },
   };
}

ALLEGRO_FONT* InputHints::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::InputHints::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::InputHints::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::string font_name = "Inter-Regular.ttf";
   int font_size = -18;

   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace AllegroFlare


