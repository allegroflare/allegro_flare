

#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


AccidentalStacker::AccidentalStacker(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches, std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack, bool solved)
   : pitches(pitches)
   , stack(stack)
   , solved(solved)
{
}


AccidentalStacker::~AccidentalStacker()
{
}


void AccidentalStacker::set_stack(std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack)
{
   this->stack = stack;
}


void AccidentalStacker::set_solved(bool solved)
{
   this->solved = solved;
}


std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> AccidentalStacker::get_pitches() const
{
   return pitches;
}


bool AccidentalStacker::get_solved() const
{
   return solved;
}


void AccidentalStacker::set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches)
{
   this->pitches = pitches;
   solved = false;
   return;
}

std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> AccidentalStacker::get_stack()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[AccidentalStacker::get_stack]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AccidentalStacker::get_stack: error: guard \"solved\" not met");
   }
   return stack;
}

void AccidentalStacker::solve()
{
   stack.clear();

   // TODO: Confirm pitches are sorted and unique, and are reversed (higher numbers at the top)

   bool top_bottom_toggle = true;
   int current_column = 0;
   //int last_ = 0;
   for (int i=0; i<pitches.size(); i++)
   {
      auto &pitch = pitches[i];

      // If pitch is not an accidental, remove it and continue
      if (!pitch.has_accidental())
      {
         pitches.erase(pitches.begin() + i);
         i--;
         continue;
      }
       
      // Place the accidental at the current column
      //int current_column = last_column;
      int pitch_staff_position = pitch.get_staff_position();
      int pitch_staff_position_normalized = pitch_staff_position % 7;
      int pitch_accidental_weight = pitch.calculate_accidental_weight();
      AccidentalType accidental_type = find_accidental_type_by_weight(pitch_accidental_weight);

      // Put it in the stack
      stack.push_back({ accidental_type, { current_column, pitch_staff_position } });

      // Erase the list of pitches
      pitches.erase(pitches.begin() + i);
      i--;
      if (pitches.empty()) continue;

      // Go through the list of pitches and look for any octaves to the current note, placing their accidentals
      // in the same column
      for (int j=0; j<pitches.size(); j++)
      {
         auto &possible_octave_to_pitch = pitches[j];
         int possible_octave_pitch_staff_position = possible_octave_to_pitch.get_staff_position();
         int possible_octave_pitch_staff_position_normalized = possible_octave_pitch_staff_position % 7;
         int possible_octave_pitch_accidental_weight = possible_octave_to_pitch.calculate_accidental_weight();
         bool is_an_octave_apart =
               (possible_octave_pitch_staff_position_normalized == pitch_staff_position_normalized)
               && (possible_octave_pitch_accidental_weight == pitch_accidental_weight);

         // This pitch is an octave apart, place it in the same column
         if (is_an_octave_apart)
         {
            AccidentalType accidental_type = find_accidental_type_by_weight(possible_octave_pitch_accidental_weight);
            stack.push_back({ accidental_type, { current_column, possible_octave_pitch_staff_position } });

            pitches.erase(pitches.begin() + j);
            i--;
            j--;
         }
      }

      current_column--;
   }

   solved = true;
   return;
}

AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType AccidentalStacker::find_accidental_type_by_weight(int accidental_weight)
{
   // TODO: Improve this calculation to permit for double sharps, double flats, etc
   if (accidental_weight == 0) return AccidentalType::NATURAL;
   else if (accidental_weight < 0) return AccidentalType::FLAT;
   else if (accidental_weight > 0) return AccidentalType::SHARP;
   return AccidentalType::UNDEFINED;
}


} // namespace MusicNotation
} // namespace AllegroFlare


