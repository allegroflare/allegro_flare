#pragma once


#include <set>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class RomanNumeralAnalysisSymbol
      {
      private:
         enum ChordQuality
         {
            UNDEFINED = 0,
            MAJOR,
            MINOR,
            DIMINISHED,
            AUGMENTED,
         };
         int scale_degree;
         RomanNumeralAnalysisSymbol::ChordQuality chord_quality;
         int inversion;
         std::vector<std::pair<int, int>> extensions;

      protected:


      public:
         RomanNumeralAnalysisSymbol();
         ~RomanNumeralAnalysisSymbol();

         void set_scale_degree(int scale_degree);
         void set_chord_quality(RomanNumeralAnalysisSymbol::ChordQuality chord_quality);
         void set_inversion(int inversion);
         void set_extensions(std::vector<std::pair<int, int>> extensions);
         int get_scale_degree() const;
         RomanNumeralAnalysisSymbol::ChordQuality get_chord_quality() const;
         int get_inversion() const;
         std::vector<std::pair<int, int>> get_extensions() const;
         std::set<int> calculate_all_chord_notes_chromatic();
         void calculate_inversion_numbers();
         std::string infer_roman_numeral_string();
      };
   }
}



