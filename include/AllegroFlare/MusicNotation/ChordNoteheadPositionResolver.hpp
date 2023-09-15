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
      public:

         enum PositionType
         {
            UNDEFINED = 0,
            LEFT,
            RIGHT,
            STEMSIDE,
         };
      private:
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches;
         std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions;
         bool solved;

      protected:


      public:
         ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={}, std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions={}, bool solved=false);
         ~ChordNoteheadPositionResolver();

         void set_solved(bool solved);
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         bool get_solved() const;
         void set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches={});
         const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& get_positions();
         void solve();
      };
   }
}



