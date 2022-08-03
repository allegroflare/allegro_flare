#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   class InputHints
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string quote;

   public:
      InputHints(AllegroFlare::FontBin* font_bin=nullptr);
      ~InputHints();

      void render();
      ALLEGRO_FONT* obtain_font();
   };
}



