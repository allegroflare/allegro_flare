#pragma once


#include <AllegroFlare/MusicNotation/Parser/PitchToken.hpp>
#include <ostream>


namespace AllegroFlare::MusicNotation::Parser
{
   bool operator==(const PitchToken& object, const PitchToken& other_object);
   bool operator!=(const PitchToken& object, const PitchToken& other_object);
   void PrintTo(const PitchToken& object, ::std::ostream* os);
}


