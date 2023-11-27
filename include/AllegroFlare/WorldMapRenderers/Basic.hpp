#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
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
         AllegroFlare::WorldMaps::Maps::Basic* map;
         std::string quote;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         Basic(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::WorldMaps::Maps::Basic* map=nullptr, std::string quote="Hello!");
         ~Basic();

         void set_map(AllegroFlare::WorldMaps::Maps::Basic* map);
         AllegroFlare::WorldMaps::Maps::Basic* get_map() const;
         void render_location(AllegroFlare::WorldMaps::Locations::Base* location=nullptr);
         void render();
      };
   }
}



