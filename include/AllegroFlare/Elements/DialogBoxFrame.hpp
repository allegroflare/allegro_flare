#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class DialogBoxFrame
      {
      public:
         static constexpr ALLEGRO_COLOR DEFAULT_BACKFILL_COLOR = ALLEGRO_COLOR{0.065f, 0.065f, 0.065f, 0.9f};
         static constexpr ALLEGRO_COLOR DEFAULT_BORDER_COLOR = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0f};

      private:
         float width;
         float height;
         float backfill_opacity;
         ALLEGRO_COLOR backfill_color;
         ALLEGRO_COLOR border_color;
         float opacity;
         float roundness;
         float border_thickness;

      protected:


      public:
         DialogBoxFrame(float width=1920/5*3, float height=1080/4);
         ~DialogBoxFrame();

         void set_width(float width);
         void set_height(float height);
         void set_backfill_opacity(float backfill_opacity);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         void set_border_color(ALLEGRO_COLOR border_color);
         void set_opacity(float opacity);
         void set_roundness(float roundness);
         void set_border_thickness(float border_thickness);
         float get_width() const;
         float get_height() const;
         float get_opacity() const;
         float get_roundness() const;
         float get_border_thickness() const;
         void render();
      };
   }
}



