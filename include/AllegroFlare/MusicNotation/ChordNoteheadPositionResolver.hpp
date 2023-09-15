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
         bool seconds_exist;
         bool solved;
         static bool custom_comparison_for_pitch_tokens(const AllegroFlare::MusicNotation::Parser::PitchToken& token1=AllegroFlare::MusicNotation::Parser::PitchToken(), const AllegroFlare::MusicNotation::Parser::PitchToken& token2=AllegroFlare::MusicNotation::Parser::PitchToken());

      protected:


      public:
         ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={}, std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions={});
         ~ChordNoteheadPositionResolver();

         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         bool get_solved() const;
         void set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches={});
         const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& get_positions();
         bool get_seconds_exist();
         const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& noteheads_exist_on_both_sides();
         void solve();
         void sort_and_make_unique();
      };
   }
}



