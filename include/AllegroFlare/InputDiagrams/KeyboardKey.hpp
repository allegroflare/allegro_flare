#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace InputDiagrams
   {
      class KeyboardKey
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string keyboard_key_str;
         ALLEGRO_COLOR color;
         float x;
         float y;
         float keyboard_key_box_height;
         float keyboard_key_box_min_width;

      public:
         KeyboardKey(AllegroFlare::FontBin* font_bin=nullptr, std::string keyboard_key_str="[unset-keyboard_key]", ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float x=0.0f, float y=0.0f, float keyboard_key_box_height=42, float keyboard_key_box_min_width=42);
         ~KeyboardKey();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_keyboard_key_str(std::string keyboard_key_str);
         void set_color(ALLEGRO_COLOR color);
         void set_x(float x);
         void set_y(float y);
         void set_keyboard_key_box_height(float keyboard_key_box_height);
         void set_keyboard_key_box_min_width(float keyboard_key_box_min_width);
         AllegroFlare::FontBin* get_font_bin();
         std::string get_keyboard_key_str();
         ALLEGRO_COLOR get_color();
         float get_x();
         float get_y();
         float get_keyboard_key_box_height();
         float get_keyboard_key_box_min_width();
         int render(bool calculate_width_only_and_do_not_draw=false);
         int calculate_width();
         int guarantee_even_number(int potentially_odd_number=0);
         ALLEGRO_FONT* obtain_font();
      };
   }
}



