#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Common.hpp>
#include <ostream>


namespace AllegroFlare::LoadASavedGame::SaveSlots
{
   bool operator==(const Common& object, const Common& other_object);
   void PrintTo(const Common& object, ::std::ostream* os);
}


