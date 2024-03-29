

#include <AllegroFlare/MusicNotation/ChordDotPositionCalculator.hpp>

#include <AllegroFlare/MusicNotation/Parser/PitchTokenSorter.hpp>


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
      int note_staff_position = pitch.staff_position;
      bool note_head_is_on_line = (note_staff_position % 2 == 0);
      int vertical_adjustment_from_being_on_line = note_head_is_on_line ? +1 : 0;
      int final_staff_position = note_staff_position + vertical_adjustment_from_being_on_line;
      result.insert(final_staff_position);
   }

   // TODO: Run a second pass to be sure that clusters with seconds would include the extra dot in the space below

   //AllegroFlare::MusicNotation::Parser::PitchTokenSorter pitch_token_sorter(pitches);
   //std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> sorted_pitches =
      //pitch_token_sorter.sort_unique_descending();

   //for (int i=1; i<sorted_pitches.size(); i++)
   //{
      //AllegroFlare::MusicNotation::Parser::PitchToken this_pitch_token
   //}

   return result;
}


} // namespace MusicNotation
} // namespace AllegroFlare


