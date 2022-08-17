#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timeline/Track.hpp>
#include <allegro5/allegro.h>
#include <cstdint>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      class TrackView
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Timeline::Track* track;

      public:
         TrackView(AllegroFlare::FontBin* font_bin=nullptr);
         ~TrackView();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         AllegroFlare::FontBin* get_font_bin();
         void render();
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
         ALLEGRO_FONT* obtain_icon_font();
      };
   }
}



