#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace WorldMapRenderers
   {
      class Basic
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Basic(AllegroFlare::FontBin* font_bin=nullptr, std::string quote="Hello!");
         ~Basic();

         void render_location(AllegroFlare::WorldMaps::Locations::Base* location=nullptr);
         void render();
      };
   }
}



