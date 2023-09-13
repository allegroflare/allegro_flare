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
      private:
         enum AccidentalType
         {
            UNDEFINED = 0,
            SHARP,
            FLAT,
            NATURAL,
         };
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
         void get_stack();
         void solve();
      };
   }
}



