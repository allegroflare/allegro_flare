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
         int selection_cursor_x;
         int icon_font_size;
         void draw_selected_node_icon(float x=0.0f, float y=0.0f);
         void draw_node_icon(float x=0.0f, float y=0.0f);
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
         ALLEGRO_FONT* obtain_icon_font();
         ALLEGRO_FONT* obtain_bigger_icon_font();
         ALLEGRO_FONT* obtain_track_values_font();

      protected:


      public:
         TrackView(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timeline::Track* track=nullptr, float x=0.0f, float y=0.0f, float width=600.0f, float height=120.0f, float value_min=0.0f, float value_max=1.0f, int selection_cursor_x=-1);
         ~TrackView();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_track(AllegroFlare::Timeline::Track* track);
         void set_x(float x);
         void set_y(float y);
         void set_width(float width);
         void set_height(float height);
         void set_value_min(float value_min);
         void set_value_max(float value_max);
         void set_selection_cursor_x(int selection_cursor_x);
         void set_icon_font_size(int icon_font_size);
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::Timeline::Track* get_track() const;
         float get_x() const;
         float get_y() const;
         float get_width() const;
         float get_height() const;
         float get_value_min() const;
         float get_value_max() const;
         int get_selection_cursor_x() const;
         int get_icon_font_size() const;
         void render();
      };
   }
}



