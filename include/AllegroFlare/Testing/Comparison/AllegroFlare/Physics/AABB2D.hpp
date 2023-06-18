#pragma once


#include <AllegroFlare/Physics/AABB2D.hpp>
#include <ostream>


namespace AllegroFlare::Physics
{
   bool operator==(const AABB2D& object, const AABB2D& other_object);
   bool operator!=(const AABB2D& object, const AABB2D& other_object);
   void PrintTo(const AABB2D& object, ::std::ostream* os);
}


