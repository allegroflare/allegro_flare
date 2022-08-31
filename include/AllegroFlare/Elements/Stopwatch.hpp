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
         AllegroFlare::Timer* timer;
         ALLEGRO_COLOR color;
         void fit_placement_width_and_height_to_stopwatch();
         std::string build_ellapsed_time_str();
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Stopwatch(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::Timer* timer=nullptr);
         ~Stopwatch();

         void set_timer(AllegroFlare::Timer* timer);
         void set_color(ALLEGRO_COLOR color);
         AllegroFlare::Timer* get_timer() const;
         ALLEGRO_COLOR get_color() const;
         void render();
      };
   }
}



