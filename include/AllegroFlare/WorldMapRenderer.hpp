#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   class WorldMapRenderer
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string quote;
      ALLEGRO_FONT* obtain_font();

   protected:


   public:
      WorldMapRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Currently not implemented");
      ~WorldMapRenderer();

      void render();
   };
}



