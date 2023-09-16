

#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>

#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


ChordNoteheadPositionResolver::ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches, std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions)
   : pitches(pitches)
   , positions(positions)
   , seconds_exist(false)
   , solved(false)
{
}


ChordNoteheadPositionResolver::~ChordNoteheadPositionResolver()
{
}


std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> ChordNoteheadPositionResolver::get_pitches() const
{
   return pitches;
}


bool ChordNoteheadPositionResolver::get_solved() const
{
   return solved;
}


void ChordNoteheadPositionResolver::set_pitches(const std::vector<AllegroFlare::MusicNotation::Parser::PitchToken>& pitches)
{
   this->pitches = pitches;
   seconds_exist = false;
   solved = false;
   return;
}

const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& ChordNoteheadPositionResolver::get_positions()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::get_positions]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::get_positions: error: guard \"solved\" not met");
   }
   return positions;
}

bool ChordNoteheadPositionResolver::get_seconds_exist()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::get_seconds_exist]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::get_seconds_exist: error: guard \"solved\" not met");
   }
   return seconds_exist;
}

int ChordNoteheadPositionResolver::lowest_staff_position_on_position_type(AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType position_type)
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::lowest_staff_position_on_position_type]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::lowest_staff_position_on_position_type: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   bool left_position_exists = false;
   int min_pitch = std::numeric_limits<float>::max();

   for (auto &position : positions)
   {
      if (position.second == position_type)
      {
         left_position_exists = true;
         if (position.first < min_pitch) min_pitch = position.first;
      }
   }

   if (left_position_exists) return min_pitch;
   return 0;
}

int ChordNoteheadPositionResolver::highest_staff_position_on_position_type(AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType position_type)
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::highest_staff_position_on_position_type]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::highest_staff_position_on_position_type: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   bool left_position_exists = false;
   int max_pitch = std::numeric_limits<float>::min();

   for (auto &position : positions)
   {
      if (position.second == position_type)
      {
         left_position_exists = true;
         if (position.first > max_pitch) max_pitch = position.first;
      }
   }

   if (left_position_exists) return max_pitch;
   return 0;
}

int ChordNoteheadPositionResolver::lowest_pitch_on_right_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::lowest_pitch_on_right_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::lowest_pitch_on_right_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return lowest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::RIGHT
      );
}

int ChordNoteheadPositionResolver::highest_pitch_on_right_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::highest_pitch_on_right_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::highest_pitch_on_right_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return highest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::RIGHT
      );
}

int ChordNoteheadPositionResolver::lowest_pitch_on_left_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::lowest_pitch_on_left_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::lowest_pitch_on_left_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return lowest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::LEFT
      );
}

int ChordNoteheadPositionResolver::highest_pitch_on_left_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::highest_pitch_on_left_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::highest_pitch_on_left_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return highest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::LEFT
      );
}

int ChordNoteheadPositionResolver::lowest_pitch_on_stemside_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::lowest_pitch_on_stemside_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::lowest_pitch_on_stemside_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return lowest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::STEMSIDE
      );
}

int ChordNoteheadPositionResolver::highest_pitch_on_stemside_column()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::highest_pitch_on_stemside_column]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::highest_pitch_on_stemside_column: error: guard \"solved\" not met");
   }
   // TODO: Test this method
   return highest_staff_position_on_position_type(
         AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType::STEMSIDE
      );
}

const std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>>& ChordNoteheadPositionResolver::noteheads_exist_on_both_sides()
{
   if (!(solved))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::noteheads_exist_on_both_sides]: error: guard \"solved\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::noteheads_exist_on_both_sides: error: guard \"solved\" not met");
   }
   return positions;
}

void ChordNoteheadPositionResolver::solve()
{
   if (!((!solved)))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::solve]: error: guard \"(!solved)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::solve: error: guard \"(!solved)\" not met");
   }
   // TODO: Sort and make unique
   sort_and_make_unique();
   std::reverse(pitches.begin(), pitches.end());

   // TODO: Test context where notes must be sorted and made unique

   // NOTE: Algorithm works generally like this:
   // 2) If there is a 2nd, the higher note is on the right side, regardless of stem direction
   // 3) The remaining notes (that are note ajacent by step to another note), are all placed either on the right
   //    side or the left side, depending on the stem direction (Stem up? Notes on left side. Stem down? Notes on
   //    right side.)
   // If the chord has a 2nd in it, there will be two columns (the stem will be on the "right side"). Depending
   // on which direction the stem is facing, it'll be up to the user to determine which side STEMSIDE stems
   // should be on.

   if (pitches.size() == 0)
   {
      // Do nothing
   }
   else if (pitches.size() == 1)
   {
      int pitch_staff_position = pitches[0].get_staff_position();
      positions.push_back({ pitch_staff_position, PositionType::STEMSIDE });
   }
   else // There are 2 or more pitches
   {
      seconds_exist = false;
      for (int i=0; i<(pitches.size() - 1); i++)
      {
         int this_note_staff_position = pitches[i].get_staff_position();
         int next_note_staff_position = pitches[i+1].get_staff_position();

         if (abs(this_note_staff_position - next_note_staff_position) == 1)
         {
            seconds_exist = true;
            break;
         }
      }

      if (!seconds_exist)
      {
         for (auto &pitch : pitches)
         {
            int pitch_staff_position = pitch.get_staff_position();
            positions.push_back({ pitch_staff_position, PositionType::STEMSIDE });
         }
      }
      else
      {
         bool this_second_right_side = true;
         bool second_placed_previously = false;

         // Place all the notes leading up to the last note
         for (int i=0; i<(pitches.size() - 1); i++)
         {
            int this_note_staff_position = pitches[i].get_staff_position();
            int next_note_staff_position = pitches[i+1].get_staff_position();

            if (abs(this_note_staff_position - next_note_staff_position) == 1)
            {
               positions.push_back({
                     this_note_staff_position,
                     this_second_right_side ? PositionType::RIGHT : PositionType::LEFT
                  });
               second_placed_previously = true;
               this_second_right_side = !this_second_right_side;
            }
            else
            {
               if (second_placed_previously)
               {
                  positions.push_back({
                        this_note_staff_position,
                        this_second_right_side ? PositionType::RIGHT : PositionType::LEFT
                     });
               }
               else // if (!second_placed_previously)
               {
                  positions.push_back({this_note_staff_position, PositionType::STEMSIDE});
               }

               second_placed_previously = false;
               this_second_right_side = true;
            }
         }

         // Place the last note
         int last_pitch_staff_position = pitches.back().get_staff_position();
         if (second_placed_previously)
         {
            positions.push_back({
                  last_pitch_staff_position,
                  this_second_right_side ? PositionType::RIGHT : PositionType::LEFT
               });
         }
         else // if (!second_placed_previously)
         {
            positions.push_back({last_pitch_staff_position, PositionType::STEMSIDE});
         }
      }
   }

   solved = true;
   return;
}

bool ChordNoteheadPositionResolver::custom_comparison_for_pitch_tokens(const AllegroFlare::MusicNotation::Parser::PitchToken& token1, const AllegroFlare::MusicNotation::Parser::PitchToken& token2)
{
   if (token1.staff_position != token2.staff_position) return token1.staff_position < token2.staff_position;
   return token1.calculate_accidental_weight() < token2.calculate_accidental_weight();
}

void ChordNoteheadPositionResolver::sort_and_make_unique()
{
   // TODO: Test this method
   std::set<
         AllegroFlare::MusicNotation::Parser::PitchToken,
         bool(*)(
               const AllegroFlare::MusicNotation::Parser::PitchToken&,
               const AllegroFlare::MusicNotation::Parser::PitchToken&
            )
      > result_pitches(
               AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::custom_comparison_for_pitch_tokens
          );

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


