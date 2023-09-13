

#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>




namespace AllegroFlare
{
namespace MusicNotation
{
namespace Parser
{


PitchToken::PitchToken(int staff_position, int accidental, bool accidental_natural)
   : staff_position(staff_position)
   , accidental(accidental)
   , accidental_natural(accidental_natural)
{
}


PitchToken::~PitchToken()
{
}


void PitchToken::set_staff_position(int staff_position)
{
   this->staff_position = staff_position;
}


void PitchToken::set_accidental(int accidental)
{
   this->accidental = accidental;
}


void PitchToken::set_accidental_natural(bool accidental_natural)
{
   this->accidental_natural = accidental_natural;
}


int PitchToken::get_staff_position() const
{
   return staff_position;
}


int PitchToken::get_accidental() const
{
   return accidental;
}


bool PitchToken::get_accidental_natural() const
{
   return accidental_natural;
}




} // namespace Parser
} // namespace MusicNotation
} // namespace AllegroFlare


