#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         class Carousel
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string quote;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Carousel(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
            ~Carousel();

            void render();
         };
      }
   }
}



