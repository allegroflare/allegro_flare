

#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>

#include <algorithm>
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

int AccidentalStacker::calculate_num_columns()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[AccidentalStacker::calculate_num_columns]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AccidentalStacker::calculate_num_columns: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   if (stack.empty()) return 0;

   int smallest_column_value = std::numeric_limits<int>::max();

   // Iterate through the collection
   for (const auto& item : stack)
   {
      int current = item.second.first; // Extract the value

      // Check if the current is smaller than the smallest found so far
      if (current < smallest_column_value)
      {
         smallest_column_value = current; // Update the smallest
      }
   }

   return std::abs(smallest_column_value);
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
               "Cannot solve. Last pitch does not have an accidental.");
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
   sort_and_make_unique();
   std::reverse(pitches.begin(), pitches.end());

   bool top_bottom_toggle = true;
   int current_column = 0;
   //int last_ = 0;
   int attempts_left = 300;
   while (!pitches.empty())
   {
      // TODO: Test this initial logic branch - when pitches at the top and the bottom do not have accidentals

      // Remove the next pitch if it does not have an accidental (depending on the current solving direction)
      if (top_bottom_toggle)
      {
         auto &pitch = pitches.front();

         // If pitch is not an accidental, remove it and continue
         if (!pitch.has_accidental())
         {
            pitches.erase(pitches.begin() + 0);
            continue;
         }
      }
      else
      {
         auto &pitch = pitches.back();

         // If pitch is not an accidental, remove it and continue
         if (!pitch.has_accidental())
         {
            pitches.pop_back();
            continue;
         }
      }

      // With this pitch that has an accidental, solve from either the top or the bottom (depending on the
      // current solving direction)
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

   integrate_fitable_columns();

   solved = true;
   return;
}

bool AccidentalStacker::can_fit(int current_column, int target_column)
{
   // TODO: Test this method
   std::vector<std::pair<AccidentalType, std::pair<int, int>>> current_column_elements;
   std::vector<std::pair<AccidentalType, std::pair<int, int>>> target_column_elements;

   for (auto &stack_item : stack)
   {
      int column = stack_item.second.first;
      if (column == current_column) current_column_elements.push_back(stack_item);
      if (column == target_column) target_column_elements.push_back(stack_item);
   }

   for (int i = 0; i < current_column_elements.size(); ++i)
   {
      for (int j = 0; j < target_column_elements.size(); ++j)
      {
         int distance = abs(i - j);
         if (distance < 6)
         {
            return false;
         }
      }
   }

   return true;
}

int AccidentalStacker::collapse_column_into_previous(int target_column)
{
   if (!(target_column < 0))
   {
      std::stringstream error_message;
      error_message << "[AccidentalStacker::collapse_column_into_previous]: error: guard \"target_column < 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AccidentalStacker::collapse_column_into_previous: error: guard \"target_column < 0\" not met");
   }
   int num_items_moved = 0;
   for (auto &stack_item : stack)
   {
      int &column = stack_item.second.first;
      if (column <= target_column)
      {
         column--;
         num_items_moved++;
      }
   }
   return num_items_moved;
}

void AccidentalStacker::integrate_fitable_columns()
{
   int current_column = 0;
   if (can_fit(0, -1)) collapse_column_into_previous(-1);
   // HERE
   // TODO: This algo
   //while()
   //{
   //}

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

bool AccidentalStacker::custom_comparison_for_pitch_tokens(const AllegroFlare::MusicNotation::Parser::PitchToken& token1, const AllegroFlare::MusicNotation::Parser::PitchToken& token2)
{
   if (token1.staff_position != token2.staff_position) return token1.staff_position < token2.staff_position;
   return token1.calculate_accidental_weight() < token2.calculate_accidental_weight();
}

void AccidentalStacker::sort_and_make_unique()
{
   // TODO: Test this method
   std::set<
         AllegroFlare::MusicNotation::Parser::PitchToken,
         bool(*)(
               const AllegroFlare::MusicNotation::Parser::PitchToken&,
               const AllegroFlare::MusicNotation::Parser::PitchToken&
            )
      > result_pitches(AllegroFlare::MusicNotation::AccidentalStacker::custom_comparison_for_pitch_tokens);

   for (auto &note : pitches)
   {
      result_pitches.insert(note);
   }

   pitches.clear();
   for (auto &note : result_pitches)
   {
      pitches.push_back(note);
   }
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare


