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

      protected:


      public:
         ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={}, std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions={});
         ~ChordNoteheadPositionResolver();

         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         bool get_solved() const;
         void set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches={});
         const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& get_positions();
         bool get_seconds_exist();
         int lowest_staff_position_on_position_type(AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType position_type=AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::UNDEFINED);
         int highest_staff_position_on_position_type(AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType position_type=AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::UNDEFINED);
         int lowest_staff_position_on_right_column();
         int highest_staff_position_on_right_column();
         int lowest_staff_position_on_left_column();
         int highest_staff_position_on_left_column();
         int lowest_staff_position_on_stemside_column();
         int highest_staff_position_on_stemside_column();
         const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& noteheads_exist_on_both_sides();
         void solve();
      };
   }
}



