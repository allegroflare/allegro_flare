

#include <AllegroFlare/MusicNotation/ChordDotPositionCalculator.hpp>




namespace AllegroFlare
{
namespace MusicNotation
{


ChordDotPositionCalculator::ChordDotPositionCalculator(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches)
   : pitches(pitches)
{
}


ChordDotPositionCalculator::~ChordDotPositionCalculator()
{
}


void ChordDotPositionCalculator::set_pitches(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches)
{
   this->pitches = pitches;
}


std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> ChordDotPositionCalculator::get_pitches() const
{
   return pitches;
}


std::set<int> ChordDotPositionCalculator::calculate_dot_staff_positions()
{
   std::set<int> result;

   for (auto &pitch : pitches)
   {
      // TODO: Collect results here
   }

   return result;
}


} // namespace MusicNotation
} // namespace AllegroFlare


