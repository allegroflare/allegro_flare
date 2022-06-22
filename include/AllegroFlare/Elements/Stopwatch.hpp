#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Stopwatch : public AllegroFlare::Elements::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Timer timer;
         ALLEGRO_COLOR color;

      public:
         Stopwatch(AllegroFlare::FontBin* font_bin=nullptr);
         ~Stopwatch();

         void set_color(ALLEGRO_COLOR color);
         ALLEGRO_COLOR get_color();
         void start();
         void pause();
         void reset();
         void is_running();
         void fit_placement_width_and_height_to_stopwatch();
         void render();
         std::string build_ellapsed_time_str();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



