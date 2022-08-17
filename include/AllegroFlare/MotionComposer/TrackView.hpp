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
         float x;
         float y;
         float width;
         float height;
         float value_min;
         float value_max;

      public:
         TrackView(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timeline::Track* track=nullptr, float x=0.0f, float y=0.0f, float width=600.0f, float height=120.0f, float value_min=0.0f, float value_max=1.0f);
         ~TrackView();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_track(AllegroFlare::Timeline::Track* track);
         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         void set_value_min(float value_min);
         void set_value_max(float value_max);
         AllegroFlare::FontBin* get_font_bin();
         AllegroFlare::Timeline::Track* get_track();
         float get_x();
         float get_y();
         float get_width();
         float get_height();
         float get_value_min();
         float get_value_max();
         void render();
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
         ALLEGRO_FONT* obtain_icon_font();
         ALLEGRO_FONT* obtain_track_values_font();
      };
   }
}



