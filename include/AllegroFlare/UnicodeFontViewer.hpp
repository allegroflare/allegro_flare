#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <cstdint>


namespace AllegroFlare
{
   class UnicodeFontViewer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      int32_t unicode_range_start;

   public:
      UnicodeFontViewer(AllegroFlare::FontBin* font_bin=nullptr);
      ~UnicodeFontViewer();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void render();
      void previous_page();
      void next_page();
      void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
      ALLEGRO_FONT* obtain_unicode_font();
      ALLEGRO_FONT* obtain_ui_font();
      ALLEGRO_FONT* obtain_ui_font_mini();
   };
}



