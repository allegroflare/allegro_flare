

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>


namespace AllegroFlare::Physics
{


bool operator==(const TileMapCollisionStepperCollisionInfo& object, const TileMapCollisionStepperCollisionInfo& other_object)
{
   //if (object.x != other_object.x) return false;
   //if (object.y != other_object.y) return false;
   return true;
}


void PrintTo(const TileMapCollisionStepperCollisionInfo& object, ::std::ostream* os)
{
   AllegroFlare::Physics::Int2D collided_tile_coordinate = object.get_collided_tile_coordinate();
   *os << "TileMapCollisionStepperCollisionInfo("
       << "{" << collided_tile_coordinate.get_x() << ", " << collided_tile_coordinate.get_y() << "}"
       << ", "
       << object.get_tile_value()
       << ", "
       << object.get_collision_velocity_x()
       << ", "
       << object.get_collision_velocity_y()
       << ", "
       << ")";
}


}


