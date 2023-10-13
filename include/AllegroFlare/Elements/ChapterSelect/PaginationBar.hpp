#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class PaginationBar : public AllegroFlare::Elements::Base
         {
         private:
            int max;
            int value;
            ALLEGRO_COLOR fill_color_reached;
            ALLEGRO_COLOR fill_color_unreached;
            float bar_width;
            float bar_spacing;
            float bar_height;
            float bar_stroke_thickness;

         protected:


         public:
            PaginationBar(int max=10, int value=10, ALLEGRO_COLOR fill_color_reached=(ALLEGRO_COLOR{1, 1, 1, 1} /*crimson*/), ALLEGRO_COLOR fill_color_unreached=(ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3} /*gray*/), float bar_width=35, float bar_spacing=60, float bar_height=6, float bar_stroke_thickness=3.0f);
            virtual ~PaginationBar();

            void set_max(int max);
            void set_value(int value);
            void set_fill_color_reached(ALLEGRO_COLOR fill_color_reached);
            void set_fill_color_unreached(ALLEGRO_COLOR fill_color_unreached);
            void set_bar_width(float bar_width);
            void set_bar_spacing(float bar_spacing);
            void set_bar_height(float bar_height);
            void set_bar_stroke_thickness(float bar_stroke_thickness);
            int get_max() const;
            int get_value() const;
            ALLEGRO_COLOR get_fill_color_reached() const;
            ALLEGRO_COLOR get_fill_color_unreached() const;
            float get_bar_width() const;
            float get_bar_spacing() const;
            float get_bar_height() const;
            float get_bar_stroke_thickness() const;
            virtual void render() override;
            void fit_placement_width_and_height();
            float calculate_width();
         };
      }
   }
}



