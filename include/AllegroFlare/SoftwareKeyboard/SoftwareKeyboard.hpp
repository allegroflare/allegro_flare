#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/SoftwareKeyboard/KeyboardKey.hpp>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace SoftwareKeyboard
   {
      class SoftwareKeyboard
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string font_name;
         int font_size;
         std::vector<AllegroFlare::SoftwareKeyboard::KeyboardKey> keys;
         int cursor_pos;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         SoftwareKeyboard(AllegroFlare::FontBin* font_bin=nullptr, std::string font_name="Inter-Medium.ttf", int font_size=-32);
         ~SoftwareKeyboard();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_font_name(std::string font_name);
         void set_font_size(int font_size);
         AllegroFlare::FontBin* get_font_bin() const;
         std::string get_font_name() const;
         int get_font_size() const;
         std::string press_key();
         void increment_cursor_pos();
         void decrement_cursor_pos();
         void render();
      };
   }
}



