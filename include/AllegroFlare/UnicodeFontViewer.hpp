#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   class UnicodeFontViewer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string font_identifier;
      uint32_t unicode_range_start;

   public:
      UnicodeFontViewer(AllegroFlare::FontBin* font_bin=nullptr, std::string font_identifier="fa-solid-900.ttf", uint32_t unicode_range_start=0x1D100);
      ~UnicodeFontViewer();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_font_identifier(std::string font_identifier);
      void set_unicode_range_start(uint32_t unicode_range_start);
      std::string get_font_identifier();
      uint32_t get_unicode_range_start();
      void render();
      void previous_page();
      void next_page();
      std::string as_hex(uint32_t value=0, int zero_fill_width=6);
      std::string as_int(uint32_t value=0);
      void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, uint32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
      ALLEGRO_FONT* obtain_unicode_font();
      ALLEGRO_FONT* obtain_ui_font();
      ALLEGRO_FONT* obtain_ui_font_mini();
   };
}



