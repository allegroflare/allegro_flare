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
         TrackView(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timeline::Track* track=nullptr);
         ~TrackView();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_track(AllegroFlare::Timeline::Track* track);
         AllegroFlare::FontBin* get_font_bin();
         AllegroFlare::Timeline::Track* get_track();
         void render();
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
         ALLEGRO_FONT* obtain_icon_font();
      };
   }
}



