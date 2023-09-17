

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MusicNotation/Parser/PitchToken.hpp>


namespace AllegroFlare::MusicNotation::Parser
{


bool operator==(const PitchToken& object, const PitchToken& other_object)
{
   if (object.staff_position != other_object.staff_position) return false;
   if (object.accidental != other_object.accidental) return false;
   if (object.accidental_natural != other_object.accidental_natural) return false;
   return true;
}


bool operator!=(const PitchToken& object, const PitchToken& other_object)
{
   return !(object == other_object);
}


void PrintTo(const PitchToken& object, ::std::ostream* os)
{
   *os << "PitchToken("
      "staff_position: " << object.staff_position << ", "
      "accidental: " << object.accidental << ", "
      "accidental_natural: " << object.accidental_natural << ", "
   ")";
}


} // AllegroFlare::MusicNotation::Parser


