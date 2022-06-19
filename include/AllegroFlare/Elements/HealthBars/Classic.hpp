#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace HealthBars
      {
         class Classic : public AllegroFlare::Elements::Base
         {
         private:
            int max;
            int value;
            ALLEGRO_COLOR color;
            float bar_width;
            float bar_spacing;
            float bar_height;
            float bar_thickness;

         public:
            Classic(int max=10, int value=10, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float bar_width=16, float bar_spacing=24, float bar_height=36, float bar_thickness=3.0f);
            ~Classic();

            void set_max(int max);
            void set_value(int value);
            void set_color(ALLEGRO_COLOR color);
            void set_bar_width(float bar_width);
            void set_bar_spacing(float bar_spacing);
            void set_bar_height(float bar_height);
            void set_bar_thickness(float bar_thickness);
            int get_max();
            int get_value();
            ALLEGRO_COLOR get_color();
            float get_bar_width();
            float get_bar_spacing();
            float get_bar_height();
            float get_bar_thickness();
            void render();
         };
      }
   }
}



