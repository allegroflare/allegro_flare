#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace InputDiagrams
   {
      class KeyboardKeyCombo
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::vector<std::string> keyboard_combo_tokens;
         ALLEGRO_COLOR color;
         float x;
         float y;
         std::string font_name;
         int font_size;
         std::string keyboard_key_font_name;
         int keyboard_key_font_size;
         float keyboard_key_box_height;
         float keyboard_key_box_min_width;
         float token_SPACE_width;
         float token_SPACER_width;
         float token_SEPARATOR_width;

      public:
         KeyboardKeyCombo(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::string> keyboard_combo_tokens={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float x=0.0f, float y=0.0f, std::string font_name="Inter-Medium.ttf", int font_size=-28, std::string keyboard_key_font_name="Inter-Medium.ttf", int keyboard_key_font_size=-20, float keyboard_key_box_height=42, float keyboard_key_box_min_width=42, float token_SPACE_width=10.0f, float token_SPACER_width=24.0f, float token_SEPARATOR_width=60.0f);
         ~KeyboardKeyCombo();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_keyboard_combo_tokens(std::vector<std::string> keyboard_combo_tokens);
         void set_color(ALLEGRO_COLOR color);
         void set_x(float x);
         void set_y(float y);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         void set_keyboard_key_font_name(std::string keyboard_key_font_name);
         void set_keyboard_key_font_size(int keyboard_key_font_size);
         void set_token_SPACE_width(float token_SPACE_width);
         void set_token_SPACER_width(float token_SPACER_width);
         void set_token_SEPARATOR_width(float token_SEPARATOR_width);
         AllegroFlare::FontBin* get_font_bin() const;
         std::vector<std::string> get_keyboard_combo_tokens() const;
         ALLEGRO_COLOR get_color() const;
         float get_x() const;
         float get_y() const;
         std::string get_font_name() const;
         int get_font_size() const;
         std::string get_keyboard_key_font_name() const;
         int get_keyboard_key_font_size() const;
         float get_keyboard_key_box_height() const;
         float get_keyboard_key_box_min_width() const;
         float get_token_SPACE_width() const;
         float get_token_SPACER_width() const;
         float get_token_SEPARATOR_width() const;
         void set_keyboard_key_box_height(float keyboard_key_box_height=42);
         int render(bool calculate_width_only_and_do_not_draw=false);
         int calculate_width();
         int guarantee_even_number(int potentially_odd_number=0);
         ALLEGRO_FONT* obtain_font();
      };
   }
}



