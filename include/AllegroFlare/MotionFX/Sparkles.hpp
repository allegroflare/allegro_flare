#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>


namespace AllegroFlare
{
   namespace MotionFX
   {
      class Sparkles
      {
      private:
         AllegroFlare::FontBin* font_bin;
         float x;
         float y;
         float created_at;

      public:
         Sparkles(AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f);
         ~Sparkles();

         void set_x(float x);
         void set_y(float y);
         void set_created_at(float created_at);
         float get_x();
         float get_y();
         float get_created_at();
         void update();
         void render();
         void is_finished();
         float infer_age();
         ALLEGRO_FONT* obtain_icon_font();
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
      };
   }
}



