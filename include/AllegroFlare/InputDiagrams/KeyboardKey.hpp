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

      public:
         KeyboardKey(AllegroFlare::FontBin* font_bin=nullptr, std::string keyboard_key_str="[unset-keyboard_key]", ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~KeyboardKey();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_keyboard_key_str(std::string keyboard_key_str);
         void set_color(ALLEGRO_COLOR color);
         AllegroFlare::FontBin* get_font_bin();
         std::string get_keyboard_key_str();
         ALLEGRO_COLOR get_color();
         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



