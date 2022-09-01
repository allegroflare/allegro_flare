#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <cstdint>
#include <string>
#include <utility>


namespace AllegroFlare
{
   namespace MusicMesh
   {
      class FontCharacterAtlasBuilder
      {
      public:
         static constexpr uint32_t UNICODE_RANGE_START = 0x1D100;

      private:
         AllegroFlare::FontBin* font_bin;
         std::string font_identifier;
         void draw_unicode_character(ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, uint32_t icon=61444, int flags=0, float x=0.0f, float y=0.0f);
         ALLEGRO_FONT* obtain_unicode_font();
         ALLEGRO_FONT* obtain_ui_font();
         ALLEGRO_FONT* obtain_ui_font_mini();
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         FontCharacterAtlasBuilder(AllegroFlare::FontBin* font_bin=nullptr, std::string font_identifier="Bravura.otf");
         ~FontCharacterAtlasBuilder();

         void set_font_identifier(std::string font_identifier);
         std::string get_font_identifier() const;
         std::pair<AllegroFlare::Vec2D, AllegroFlare::Vec2D> get_uv_for_index(uint32_t unicode_index=0);
         ALLEGRO_BITMAP* create();
         std::string as_hex(uint32_t value=0, int zero_fill_width=6);
         std::string as_int(uint32_t value=0);
      };
   }
}



