

#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


ChordNoteheadPositionResolver::ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches, std::vector<std::pair<int, AllegroFlare::MusicNotation::ChordNoteheadPositionResolver::PositionType>> positions, bool solved)
   : pitches(pitches)
   , positions(positions)
   , solved(solved)
{
}


ChordNoteheadPositionResolver::~ChordNoteheadPositionResolver()
{
}


void ChordNoteheadPositionResolver::set_solved(bool solved)
{
   this->solved = solved;
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

void ChordNoteheadPositionResolver::solve()
{
   if (!((!solved)))
   {
      std::stringstream error_message;
      error_message << "[ChordNoteheadPositionResolver::solve]: error: guard \"(!solved)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ChordNoteheadPositionResolver::solve: error: guard \"(!solved)\" not met");
   }
   // NOTE: Algorithm works generally like this:
   // 2) If there is a 2nd, the higher note is on the right side, regardless of stem direction
   // 3) The remaining notes (that are note ajacent by step to another note), are all placed either on the right
   //    side or the left side, depending on the stem direction (Stem up? Notes on left side. Stem down? Notes on
   //    right side.)
   // If the chord has a 2nd in it, there will be two columns (the stem will be on the "right side").

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
      bool seconds_exist = false;
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
            // bool last_note = (i == pitches.size() - 1); // last_note
            //bool this_second_right_side = true;
            //bool second_placed_previously = false;
            //int previous_note_position = 0;
            //int this_note_position = 0;
            int this_note_staff_position = pitches[i].get_staff_position();
            int next_note_staff_position = pitches[i+1].get_staff_position();

            if (abs(this_note_staff_position - next_note_staff_position) == 1)
            {
               positions.push_back({
                     this_note_staff_position,
                     this_second_right_side ? PositionType::RIGHT : PositionType::LEFT
                  });
               second_placed_previously = true;
               //seconds_exist = true;
               //break;
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


} // namespace MusicNotation
} // namespace AllegroFlare


