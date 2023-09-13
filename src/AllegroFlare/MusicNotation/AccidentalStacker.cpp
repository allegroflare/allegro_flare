

#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>

#include <iostream>
#include <set>
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

void AccidentalStacker::solve_one_from_top(int column_to_place_on)
{
   if (!((!pitches.empty())))
   {
      std::stringstream error_message;
      error_message << "[AccidentalStacker::solve_one_from_top]: error: guard \"(!pitches.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AccidentalStacker::solve_one_from_top: error: guard \"(!pitches.empty())\" not met");
   }
   auto &pitch = pitches.front();

      if (!pitch.has_accidental())
      {
         // TODO: Replace with AllegroFlare::Logger error
         throw std::runtime_error("AccidentalStacker::solve_one_from_top: error: "
               "Cannot solve. First pitch does not have an accidental.");
      }
       
      // Place the accidental at the current column
      int pitch_staff_position = pitch.get_staff_position();
      int pitch_staff_position_normalized = pitch_staff_position % 7;
      int pitch_accidental_weight = pitch.calculate_accidental_weight();
      AccidentalType accidental_type = find_accidental_type_by_weight(pitch_accidental_weight);

      // Put it in the stack
      stack.push_back({ accidental_type, { column_to_place_on, pitch_staff_position } });

      // Erase the list of pitches
      pitches.erase(pitches.begin() + 0);
      if (pitches.empty()) return;

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
            stack.push_back({ accidental_type, { column_to_place_on, possible_octave_pitch_staff_position } });

            pitches.erase(pitches.begin() + j);
            //i--;
            j--;
         }
      }
   return;
}

void AccidentalStacker::solve_one_from_bottom(int column_to_place_on)
{
   if (!((!pitches.empty())))
   {
      std::stringstream error_message;
      error_message << "[AccidentalStacker::solve_one_from_bottom]: error: guard \"(!pitches.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AccidentalStacker::solve_one_from_bottom: error: guard \"(!pitches.empty())\" not met");
   }
   auto &pitch = pitches.back();

      if (!pitch.has_accidental())
      {
         // TODO: Replace with AllegroFlare::Logger error
         throw std::runtime_error("AccidentalStacker::solve_one_from_top: error: "
               "Cannot solve. First pitch does not have an accidental.");
      }
       
      // Place the accidental at the current column
      int pitch_staff_position = pitch.get_staff_position();
      int pitch_staff_position_normalized = pitch_staff_position % 7;
      int pitch_accidental_weight = pitch.calculate_accidental_weight();
      AccidentalType accidental_type = find_accidental_type_by_weight(pitch_accidental_weight);

      // Put it in the stack
      stack.push_back({ accidental_type, { column_to_place_on, pitch_staff_position } });

      // Erase the list of pitches
      pitches.pop_back();
      if (pitches.empty()) return;

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
            stack.push_back({ accidental_type, { column_to_place_on, possible_octave_pitch_staff_position } });

            pitches.erase(pitches.begin() + j);
            //i--;
            j--;
         }
      }
   return;
}

void AccidentalStacker::solve()
{
   stack.clear();

   // TODO: Confirm pitches are sorted and unique, and are reversed (higher numbers at the top)

   bool top_bottom_toggle = true;
   int current_column = 0;
   //int last_ = 0;
   int attempts_left = 300;
   while (!pitches.empty())
   {
      auto &pitch = pitches.front();

      // If pitch is not an accidental, remove it and continue
      if (!pitch.has_accidental())
      {
         pitches.erase(pitches.begin() + 0);
         continue;
      }

      // With this pitch that has an accidental, solve from either the top or the bottom (depending on the
      // current solving direction
      if (top_bottom_toggle)
      {
         solve_one_from_top(current_column);
      }
      else
      {
         solve_one_from_bottom(current_column);
      }

      // Toggle the direction for the next pass
      top_bottom_toggle = !top_bottom_toggle;

      // Shift the column to the left by one
      current_column--;

      // Decrement out attempts_left counter to prevent an infinite loop
      attempts_left--;
      if (attempts_left <= 0) throw std::runtime_error("AccidentalStacker::error: too many attempts");
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

bool AccidentalStacker::operator()(const AllegroFlare::MusicNotation::Parser::PitchToken& token1, const AllegroFlare::MusicNotation::Parser::PitchToken& token2)
{
   // TODO: Test this comparitor
   if (token1.staff_position != token2.staff_position) return token1.staff_position < token2.staff_position;
   return token1.calculate_accidental_weight() < token2.calculate_accidental_weight();
}

void AccidentalStacker::sort_and_make_unique()
{
   // TODO: Consider modifying this method to return a sorted object rather than modify the existing one
   std::set<
         AllegroFlare::MusicNotation::Parser::PitchToken,
         AllegroFlare::MusicNotation::AccidentalStacker
      > result_multi_note;
   //std::set<PitchToken, PitchTokenComparator> result_multi_note;

   //for (auto &note : multi_note)
   //{
      //result_multi_note.insert(note);
   //}

   //multi_note.clear();
   //for (auto &note : result_multi_note)
   //{
      //multi_note.push_back(note);
   //}
}


} // namespace MusicNotation
} // namespace AllegroFlare


