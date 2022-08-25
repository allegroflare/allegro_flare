#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace HealthBars
      {
         class Basic : public AllegroFlare::Elements::Base
         {
         private:
            float value;
            float max;
            ALLEGRO_COLOR fill_color;
            ALLEGRO_COLOR backfill_color;
            float bar_width;
            float bar_height;
            float min_render_threshold;

         public:
            Basic(float value=1.0, float max=1.0, ALLEGRO_COLOR fill_color=(ALLEGRO_COLOR{0.0, 0.75, 1.0, 1} /*deep sky blue*/), ALLEGRO_COLOR backfill_color=(ALLEGRO_COLOR{0.1, 0.1, 0.1, 0.9}), float bar_width=200, float bar_height=16, float min_render_threshold=0.0001);
            ~Basic();

            void set_value(float value);
            void set_max(float max);
            void set_fill_color(ALLEGRO_COLOR fill_color);
            void set_backfill_color(ALLEGRO_COLOR backfill_color);
            void set_bar_width(float bar_width);
            void set_bar_height(float bar_height);
            void set_min_render_threshold(float min_render_threshold);
            float get_value() const;
            float get_max() const;
            ALLEGRO_COLOR get_fill_color() const;
            ALLEGRO_COLOR get_backfill_color() const;
            float get_bar_width() const;
            float get_bar_height() const;
            float get_min_render_threshold() const;
            void render();
         };
      }
   }
}



