#pragma once


#include <allegro5/allegro_color.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class Scrollbar
      {
      private:
         float x;
         float y;
         float height;
         float position;
         ALLEGRO_COLOR bar_color;
         ALLEGRO_COLOR handle_color;
         float handle_height;
         float rail_thickness;
         float handle_thickness;

      public:
         Scrollbar(float x=0.0f, float y=0.0f, float height=100.0f, float position=0.0f, ALLEGRO_COLOR bar_color=ALLEGRO_COLOR{0.4, 0.405, 0.41, 1.0}, ALLEGRO_COLOR handle_color=ALLEGRO_COLOR{0.7, 0.705, 0.71, 1.0}, float handle_height=50.0f, float rail_thickness=8.0f, float handle_thickness=16.0f);
         ~Scrollbar();

         void set_x(float x);
         void set_y(float y);
         void set_height(float height);
         void set_position(float position);
         void set_bar_color(ALLEGRO_COLOR bar_color);
         void set_handle_color(ALLEGRO_COLOR handle_color);
         void set_handle_height(float handle_height);
         void set_rail_thickness(float rail_thickness);
         void set_handle_thickness(float handle_thickness);
         float get_x();
         float get_y();
         float get_height();
         float get_position();
         ALLEGRO_COLOR get_bar_color();
         ALLEGRO_COLOR get_handle_color();
         float get_handle_height();
         float get_rail_thickness();
         float get_handle_thickness();
         void render();
      };
   }
}



