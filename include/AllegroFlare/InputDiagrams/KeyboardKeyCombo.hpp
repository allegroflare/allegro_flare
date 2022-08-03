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

      public:
         KeyboardKeyCombo(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::string> keyboard_combo_tokens={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float x=0.0f, float y=0.0f);
         ~KeyboardKeyCombo();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_keyboard_combo_tokens(std::vector<std::string> keyboard_combo_tokens);
         void set_color(ALLEGRO_COLOR color);
         void set_x(float x);
         void set_y(float y);
         AllegroFlare::FontBin* get_font_bin();
         std::vector<std::string> get_keyboard_combo_tokens();
         ALLEGRO_COLOR get_color();
         float get_x();
         float get_y();
         float get_keyboard_key_box_height();
         float render(bool calculate_width_only_and_do_not_draw=false);
         float calculate_width();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



