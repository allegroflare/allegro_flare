

#include <AllegroFlare/MusicNotation/Parser/PitchTokenSorter.hpp>

#include <algorithm>
#include <set>


namespace AllegroFlare
{
namespace MusicNotation
{
namespace Parser
{


PitchTokenSorter::PitchTokenSorter(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches)
   : pitches(pitches)
{
}


PitchTokenSorter::~PitchTokenSorter()
{
}


void PitchTokenSorter::set_pitches(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches)
{
   this->pitches = pitches;
}


std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> PitchTokenSorter::get_pitches() const
{
   return pitches;
}


std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> PitchTokenSorter::sort_unique_descending()
{
   std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> result;
   // TODO: Test this method
   std::set<
         AllegroFlare::MusicNotation::Parser::PitchToken,
         bool(*)(
               const AllegroFlare::MusicNotation::Parser::PitchToken&,
               const AllegroFlare::MusicNotation::Parser::PitchToken&
            )
      > result_set_pitches(
               AllegroFlare::MusicNotation::Parser::PitchTokenSorter::custom_comparison_for_pitch_tokens
          );

   // Add existing pitches to the 
   for (auto &note : pitches)
   {
      result_set_pitches.insert(note);
   }

   //pitches.clear();
   for (auto &note : result_set_pitches)
   {
      result.push_back(note);
   }

   // Make the list of pitches descending (so that higher pitches are at the top)
   std::reverse(result.begin(), result.end());

   return result;
}

bool PitchTokenSorter::custom_comparison_for_pitch_tokens(const AllegroFlare::MusicNotation::Parser::PitchToken& token1, const AllegroFlare::MusicNotation::Parser::PitchToken& token2)
{
   if (token1.staff_position != token2.staff_position) return token1.staff_position < token2.staff_position;
   return token1.calculate_accidental_weight() < token2.calculate_accidental_weight();
}


} // namespace Parser
} // namespace MusicNotation
} // namespace AllegroFlare


