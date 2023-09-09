#pragma once


#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class RomanNumeralAnalysisSymbol
      {
      public:

         enum ChordQuality
         {
            UNDEFINED = 0,
            MAJOR,
            MINOR,
            DIMINISHED,
            AUGMENTED,
         };
      private:
         int scale_degree;
         int accidental;
         RomanNumeralAnalysisSymbol::ChordQuality chord_quality;
         int inversion;
         std::vector<std::pair<int, int>> extensions;

      protected:


      public:
         RomanNumeralAnalysisSymbol();
         ~RomanNumeralAnalysisSymbol();

         void set_scale_degree(int scale_degree);
         void set_accidental(int accidental);
         void set_chord_quality(RomanNumeralAnalysisSymbol::ChordQuality chord_quality);
         void set_inversion(int inversion);
         void set_extensions(std::vector<std::pair<int, int>> extensions);
         int get_scale_degree() const;
         int get_accidental() const;
         RomanNumeralAnalysisSymbol::ChordQuality get_chord_quality() const;
         int get_inversion() const;
         std::vector<std::pair<int, int>> get_extensions() const;
         std::vector<std::pair<int, int>> calculate_inversion_notes_with_extensions();
         void calculate_inversion_numbers();
         std::string infer_roman_numeral_string();
      };
   }
}



