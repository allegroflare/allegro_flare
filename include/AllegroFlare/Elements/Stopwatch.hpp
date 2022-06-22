#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Timer.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class Stopwatch : public AllegroFlare::Elements::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Timer timer;

      public:
         Stopwatch(AllegroFlare::FontBin* font_bin=nullptr);
         ~Stopwatch();

         void start();
         void pause();
         void reset();
         void is_running();
         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



