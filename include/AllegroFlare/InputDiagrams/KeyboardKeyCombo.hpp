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

      public:
         KeyboardKeyCombo(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::string> keyboard_combo_tokens={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float x=0.0f, float y=0.0f, std::string font_name="Inter-Medium.ttf", int font_size=-28, std::string keyboard_key_font_name="Inter-Medium.ttf", int keyboard_key_font_size=-20);
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
         AllegroFlare::FontBin* get_font_bin();
         std::vector<std::string> get_keyboard_combo_tokens();
         ALLEGRO_COLOR get_color();
         float get_x();
         float get_y();
         std::string get_font_name();
         int get_font_size();
         std::string get_keyboard_key_font_name();
         int get_keyboard_key_font_size();
         float get_keyboard_key_box_height();
         int render(bool calculate_width_only_and_do_not_draw=false);
         int calculate_width();
         int guarantee_even_number(int potentially_odd_number=0);
         ALLEGRO_FONT* obtain_font();
      };
   }
}



