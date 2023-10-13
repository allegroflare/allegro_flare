#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class PaginationBar : public AllegroFlare::Elements::Base
         {
         private:
            std::vector<bool> elements;
            int cursor_position;
            ALLEGRO_COLOR fill_color_reached;
            ALLEGRO_COLOR fill_color_unreached;
            ALLEGRO_COLOR cursor_stroke_line_color;
            float cursor_stroke_line_thickness;
            float bar_width;
            float bar_spacing;
            float bar_height;
            float bar_stroke_thickness;

         protected:


         public:
            PaginationBar(std::vector<bool> elements={}, int cursor_position=0, ALLEGRO_COLOR fill_color_reached=(ALLEGRO_COLOR{1, 1, 1, 1} /*white*/), ALLEGRO_COLOR fill_color_unreached=(ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3} /*gray*/), ALLEGRO_COLOR cursor_stroke_line_color=(ALLEGRO_COLOR{1, 1, 1, 1} /*white*/), float cursor_stroke_line_thickness=2.0, float bar_width=35, float bar_spacing=60, float bar_height=6, float bar_stroke_thickness=3.0f);
            virtual ~PaginationBar();

            void set_elements(std::vector<bool> elements);
            void set_cursor_position(int cursor_position);
            void set_fill_color_reached(ALLEGRO_COLOR fill_color_reached);
            void set_fill_color_unreached(ALLEGRO_COLOR fill_color_unreached);
            void set_cursor_stroke_line_color(ALLEGRO_COLOR cursor_stroke_line_color);
            void set_cursor_stroke_line_thickness(float cursor_stroke_line_thickness);
            void set_bar_width(float bar_width);
            void set_bar_spacing(float bar_spacing);
            void set_bar_height(float bar_height);
            void set_bar_stroke_thickness(float bar_stroke_thickness);
            std::vector<bool> get_elements() const;
            int get_cursor_position() const;
            ALLEGRO_COLOR get_fill_color_reached() const;
            ALLEGRO_COLOR get_fill_color_unreached() const;
            ALLEGRO_COLOR get_cursor_stroke_line_color() const;
            float get_cursor_stroke_line_thickness() const;
            float get_bar_width() const;
            float get_bar_spacing() const;
            float get_bar_height() const;
            float get_bar_stroke_thickness() const;
            virtual void render() override;
            void fit_placement_width_and_height();
            float calculate_width();
            int get_num_elements();
         };
      }
   }
}



