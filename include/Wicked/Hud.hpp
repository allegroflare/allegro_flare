#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>


namespace Wicked
{
   class Hud
   {
   private:
      AllegroFlare::FontBin* font_bin;
      int score;
      int health;
      ALLEGRO_FONT* obtain_hud_text_font();

   protected:


   public:
      Hud(AllegroFlare::FontBin* font_bin=nullptr);
      ~Hud();

      void set_font_bin(AllegroFlare::FontBin* font_bin);
      void set_score(int score);
      void set_health(int health);
      int get_score() const;
      int get_health() const;
      void primary_timer_func();
      void render();
      void draw_health();
      void draw_score();
   };
}


