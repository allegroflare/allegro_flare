#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class DialogOverlay
         {
         private:
            AllegroFlare::FontBin* font_bin;
            std::string quote;
            ALLEGRO_FONT* obtain_font();

         protected:


         public:
            DialogOverlay(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
            ~DialogOverlay();

            void render();
         };
      }
   }
}



