#pragma once


#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>
#include <set>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class ChordDotPositionCalculator
      {
      private:
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches;

      protected:


      public:
         ChordDotPositionCalculator(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches={});
         ~ChordDotPositionCalculator();

         void set_pitches(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches);
         std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> get_pitches() const;
         std::set<int> calculate_dot_staff_positions();
      };
   }
}



