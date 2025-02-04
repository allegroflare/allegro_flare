

#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>

#include <AllegroFlare/MusicNotation/Parser/PitchTokenSorter.hpp>
#include <iostream>
#include <limits>
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
      error_message << "[AllegroFlare::MusicNotation::AccidentalStacker::get_stack]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::AccidentalStacker::get_stack]: error: guard \"solved\" not met");
   }
   return stack;
}

int AccidentalStacker::calculate_num_columns()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::AccidentalStacker::calculate_num_columns]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::AccidentalStacker::calculate_num_columns]: error: guard \"solved\" not met");
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
      error_message << "[AllegroFlare::MusicNotation::AccidentalStacker::solve_one_from_top]: error: guard \"(!pitches.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::AccidentalStacker::solve_one_from_top]: error: guard \"(!pitches.empty())\" not met");
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
      for (int j=0; j<(int)pitches.size(); j++)
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
      error_message << "[AllegroFlare::MusicNotation::AccidentalStacker::solve_one_from_bottom]: error: guard \"(!pitches.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::AccidentalStacker::solve_one_from_bottom]: error: guard \"(!pitches.empty())\" not met");
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
      for (int j=0; j<(int)pitches.size(); j++)
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

   // Sort notes for this operation
   // TODO: Test context where notes must be sorted and made unique
   AllegroFlare::MusicNotation::Parser::PitchTokenSorter pitch_token_sorter(pitches);
   pitches = pitch_token_sorter.sort_unique_descending();


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

   for (int i=0; i<(int)current_column_elements.size(); ++i)
   {
      for (int j=0; j<(int)target_column_elements.size(); ++j)
      {
         int row_of_current_item = current_column_elements[i].second.second;
         int row_of_target_item = target_column_elements[j].second.second;

         int distance = abs(row_of_current_item - row_of_target_item);
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
      error_message << "[AllegroFlare::MusicNotation::AccidentalStacker::collapse_column_into_previous]: error: guard \"target_column < 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::AccidentalStacker::collapse_column_into_previous]: error: guard \"target_column < 0\" not met");
   }
   int num_items_moved = 0;
   for (auto &stack_item : stack)
   {
      int &column = stack_item.second.first;
      if (column <= target_column)
      {
         column++;
         num_items_moved++;
         std::cout << "smush - " << std::endl; 
      }
   }
   return num_items_moved;
}

void AccidentalStacker::integrate_fitable_columns()
{
   int current_column = 0;

   // TODO: Make this into an actual algorithm. This is brute force, and assumes 4 columns are a max stackable
   // TODO: Test this with better coverage
   if (can_fit(0, -1)) collapse_column_into_previous(-1);
   if (can_fit(0, -1)) collapse_column_into_previous(-1);
   if (can_fit(0, -1)) collapse_column_into_previous(-1);
   if (can_fit(0, -1)) collapse_column_into_previous(-1);
   if (can_fit(-1, -2)) collapse_column_into_previous(-2);
   if (can_fit(-1, -2)) collapse_column_into_previous(-2);
   if (can_fit(-1, -2)) collapse_column_into_previous(-2);
   if (can_fit(-1, -2)) collapse_column_into_previous(-2);
   if (can_fit(-2, -3)) collapse_column_into_previous(-3);
   if (can_fit(-2, -3)) collapse_column_into_previous(-3);
   if (can_fit(-2, -3)) collapse_column_into_previous(-3);
   if (can_fit(-2, -3)) collapse_column_into_previous(-3);
   if (can_fit(-3, -4)) collapse_column_into_previous(-4);
   if (can_fit(-3, -4)) collapse_column_into_previous(-4);
   if (can_fit(-3, -4)) collapse_column_into_previous(-4);
   if (can_fit(-3, -4)) collapse_column_into_previous(-4);

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


