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
            ALLEGRO_COLOR fill_color;
            ALLEGRO_COLOR empty_box_outline_color;
            float bar_width;
            float bar_spacing;
            float bar_height;
            float bar_stroke_thickness;

         protected:


         public:
            Classic(int max=10, int value=10, ALLEGRO_COLOR fill_color=(ALLEGRO_COLOR{0.86, 0.08, 0.24, 1} /*crimson*/), ALLEGRO_COLOR empty_box_outline_color=(ALLEGRO_COLOR{1, 1, 1, 1} /*white*/), float bar_width=16, float bar_spacing=24, float bar_height=36, float bar_stroke_thickness=3.0f);
            ~Classic();

            void set_max(int max);
            void set_value(int value);
            void set_fill_color(ALLEGRO_COLOR fill_color);
            void set_empty_box_outline_color(ALLEGRO_COLOR empty_box_outline_color);
            void set_bar_width(float bar_width);
            void set_bar_spacing(float bar_spacing);
            void set_bar_height(float bar_height);
            void set_bar_stroke_thickness(float bar_stroke_thickness);
            int get_max() const;
            int get_value() const;
            ALLEGRO_COLOR get_fill_color() const;
            ALLEGRO_COLOR get_empty_box_outline_color() const;
            float get_bar_width() const;
            float get_bar_spacing() const;
            float get_bar_height() const;
            float get_bar_stroke_thickness() const;
            void render() override;
            void fit_placement_width_and_height();
            float calculate_width();
         };
      }
   }
}



