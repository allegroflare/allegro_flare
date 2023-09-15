

#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


ChordNoteheadPositionResolver::ChordNoteheadPositionResolver(std::vector<AllegroFlare::MusicNotation::Parser::PitchToken> pitches, std::vector<std::pair<int, int>> positions, bool solved)
   : pitches(pitches)
   , positions(positions)
   , solved(solved)
{
}


ChordNoteheadPositionResolver::~ChordNoteheadPositionResolver()
{
}


void ChordNoteheadPositionResolver::set_positions(std::vector<std::pair<int, int>> positions)
{
   this->positions = positions;
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

const std::vector<std::pair<int, int>>& ChordNoteheadPositionResolver::get_positions()
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
   // TODO: This implementation

   // 1) If the chord has a 2nd in it, there will be two columns, and the beam will be on the "right side"
   // 2) If there is a 2nd, the higher note is on the right side, regardless of stem direction
   // 3) The remaining notes (that are note ajacent by step to another note), are all placed either on the right
   //    side or the left side, depending on the stem direction (Stem up? Notes on left side. Stem down? Notes on
   //    right side.)

   solved = true;
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare


