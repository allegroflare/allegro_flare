#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/WorldMaps/Locations/Base.hpp>
#include <AllegroFlare/WorldMaps/Maps/Basic.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace AllegroFlare
{
   namespace WorldMapRenderers
   {
      class Basic
      {
      private:
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::WorldMaps::Maps::Basic* map;
         std::string quote;
         ALLEGRO_FONT* obtain_font();
         ALLEGRO_BITMAP* obtain_background_image();

      protected:


      public:
         Basic(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::WorldMaps::Maps::Basic* map=nullptr, std::string quote="Hello!");
         ~Basic();

         void set_map(AllegroFlare::WorldMaps::Maps::Basic* map);
         AllegroFlare::WorldMaps::Maps::Basic* get_map() const;
         void draw_point(float x=0.0f, float y=0.0f, ALLEGRO_COLOR point_color=ALLEGRO_COLOR{0.96, 0.89, 0.5, 1.0});
         void render_location(AllegroFlare::WorldMaps::Locations::Base* location=nullptr);
         void render();
      };
   }
}



