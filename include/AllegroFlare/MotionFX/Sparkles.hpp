#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace MotionFX
   {
      class Sparkles
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;
         float created_at;

      public:
         Sparkles(AllegroFlare::FontBin* font_bin=nullptr);
         ~Sparkles();

         void set_created_at(float created_at);
         float get_created_at();
         void update();
         void render();
         void is_finished();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



