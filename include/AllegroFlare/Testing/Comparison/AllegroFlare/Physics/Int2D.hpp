#pragma once


#include <AllegroFlare/Physics/Int2D.hpp>
#include <ostream>


namespace AllegroFlare::Physics
{
   bool operator==(const Int2D& object, const Int2D& other_object);
   bool operator!=(const Int2D& object, const Int2D& other_object);
   void PrintTo(const Int2D& object, ::std::ostream* os);
}


