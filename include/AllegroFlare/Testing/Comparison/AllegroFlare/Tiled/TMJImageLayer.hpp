#pragma once


#include <AllegroFlare/Tiled/TMJImageLayer.hpp>
#include <ostream>


namespace AllegroFlare::Tiled
{
   bool operator==(const TMJImageLayer& object, const TMJImageLayer& other_object);
   bool operator!=(const TMJImageLayer& object, const TMJImageLayer& other_object);
   void PrintTo(const TMJImageLayer& object, ::std::ostream* os);
}


