#pragma once


#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class ChordNoteheadPositionResolver
      {
      private:
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches;
         std::vector<std::pair<int, int>> positions;
         bool solved;

      protected:


      public:
         ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={}, std::vector<std::pair<int, int>> positions={}, bool solved=false);
         ~ChordNoteheadPositionResolver();

         void set_positions(std::vector<std::pair<int, int>> positions);
         void set_solved(bool solved);
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         bool get_solved() const;
         void set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches={});
         const std::vector<std::pair<int, int>>& get_positions();
         void solve();
      };
   }
}



