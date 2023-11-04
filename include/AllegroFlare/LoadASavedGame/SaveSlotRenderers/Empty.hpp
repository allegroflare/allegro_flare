#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlotRenderers
      {
         class Empty
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string quote;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            Empty(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
            ~Empty();

            void render();
         };
      }
   }
}



