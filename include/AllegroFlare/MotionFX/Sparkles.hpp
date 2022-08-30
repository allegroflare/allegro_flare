#pragma once


#include <ALLEGRO_FONT.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <tuple>
#include <vector>


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
         std::vector<std::tuple<float, float, float, ALLEGRO_COLOR>> particles;
         float created_at;
         bool initialized;
         AllegroFlare::Placement2D main_star_placement;

      public:
         Sparkles(AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f);
         ~Sparkles();

         void set_x(float x);
         void set_y(float y);
         void set_created_at(float created_at);
         float get_x() const;
         float get_y() const;
         float get_created_at() const;
         bool get_initialized() const;
         void initialize();
         void update();
         void render();
         void is_finished();
         float infer_age();
         ALLEGRO_FONT* obtain_icon_font();
         ALLEGRO_FONT* obtain_mini_icon_font();
         void draw_centered_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, int x=0, int y=0, uint32_t icon=0xf005, int flags=0);
      };
   }
}



