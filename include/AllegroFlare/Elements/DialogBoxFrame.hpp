#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxFrame
      {
      private:
         float width;
         float height;
         float opacity;
         ALLEGRO_COLOR fill_color;
         ALLEGRO_COLOR border_color;

      public:
         DialogBoxFrame(float width=1920/5*3, float height=1080/4);
         ~DialogBoxFrame();

         void set_opacity(float opacity);
         void set_fill_color(ALLEGRO_COLOR fill_color);
         void set_border_color(ALLEGRO_COLOR border_color);
         float get_width();
         float get_height();
         void render();
      };
   }
}



