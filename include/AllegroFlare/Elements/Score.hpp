#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class Score
      {
      private:
         AllegroFlare::FontBin* font_bin;
         int score;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Score(AllegroFlare::FontBin* font_bin=nullptr, int score=0);
         ~Score();

         void render();
         std::string get_score_str();
      };
   }
}



