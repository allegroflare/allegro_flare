#pragma once


#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class AccidentalStacker
      {
      public:

         enum AccidentalType
         {
            UNDEFINED = 0,
            SHARP,
            FLAT,
            NATURAL,
         };
      private:
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches;
         std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack;
         bool solved;

      protected:


      public:
         AccidentalStacker(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={}, std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack={}, bool solved=false);
         ~AccidentalStacker();

         void set_stack(std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack);
         void set_solved(bool solved);
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         bool get_solved() const;
         void set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches={});
         std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> get_stack();
         void solve_one_from_top(int column_to_place_on=0);
         void solve_one_from_bottom(int column_to_place_on=0);
         void solve();
         static AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType find_accidental_type_by_weight(int accidental_weight=0);
      };
   }
}



