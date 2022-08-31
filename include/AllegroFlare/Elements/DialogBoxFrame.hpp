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
         float backfill_opacity;
         ALLEGRO_COLOR backfill_color;
         ALLEGRO_COLOR border_color;
         float opacity;

      protected:


      public:
         DialogBoxFrame(float width=1920/5*3, float height=1080/4);
         ~DialogBoxFrame();

         void set_backfill_opacity(float backfill_opacity);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         void set_border_color(ALLEGRO_COLOR border_color);
         void set_opacity(float opacity);
         float get_width() const;
         float get_height() const;
         float get_opacity() const;
         void render();
      };
   }
}



