#pragma once


#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class RomanNumeralAnalysisSymbolRenderer
      {
      private:
         AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol;

      protected:


      public:
         RomanNumeralAnalysisSymbolRenderer(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol=nullptr);
         ~RomanNumeralAnalysisSymbolRenderer();

         void set_symbol(AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* symbol);
         AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol* get_symbol() const;
         void render();
      };
   }
}



