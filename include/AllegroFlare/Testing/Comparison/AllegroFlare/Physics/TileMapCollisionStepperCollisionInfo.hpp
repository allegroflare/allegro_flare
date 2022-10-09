#pragma once


#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <ostream>


namespace AllegroFlare::Physics
{
   bool operator==(const TileMapCollisionStepperCollisionInfo& object, const TileMapCollisionStepperCollisionInfo& other_object);
   void PrintTo(const TileMapCollisionStepperCollisionInfo& object, ::std::ostream* os);
}


