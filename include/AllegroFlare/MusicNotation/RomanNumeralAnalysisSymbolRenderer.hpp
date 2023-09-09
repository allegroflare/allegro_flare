#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>
#include <allegro5/allegro_font.h>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class RomanNumeralAnalysisSymbolRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol;
         float x;
         float y;
         int primary_symbol_font_size;

      protected:


      public:
         RomanNumeralAnalysisSymbolRenderer(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol=nullptr, float x=0, float y=0, int primary_symbol_font_size=30);
         ~RomanNumeralAnalysisSymbolRenderer();

         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_symbol(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol);
         void set_x(float x);
         void set_y(float y);
         void set_primary_symbol_font_size(int primary_symbol_font_size);
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* get_symbol() const;
         float get_x() const;
         float get_y() const;
         int get_primary_symbol_font_size() const;
         void render();
         ALLEGRO_FONT* obtain_primary_symbol_font();
      };
   }
}



