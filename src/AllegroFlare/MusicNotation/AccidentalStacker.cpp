

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
   for (int i=0; i<pitches.size(); i++)
   {
      auto &pitch = pitches[i];

      if (!pitch.has_accidental())
      {
         pitches.erase(pitches.begin() + i);
         i--;
         continue;
      }
       
      // Take one off the top
      //int pitch_staff_position = pitch.get_staff_position();
      //int pitch_accidental = pitch.get_staff_position();
      //stack.push_back
   }

   solved = true;
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare


