

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Physics/Int2D.hpp>


namespace AllegroFlare::Physics
{


bool operator==(
      const TileMapCollisionStepperCollisionInfo& object,
      const TileMapCollisionStepperCollisionInfo& other_object
   )
{
   AllegroFlare::Physics::Int2D collided_tile_coordinate = object.get_collided_tile_coordinate();
   AllegroFlare::Physics::Int2D other_collided_tile_coordinate = other_object.get_collided_tile_coordinate();

   if (collided_tile_coordinate != other_collided_tile_coordinate) return false;
   if (object.get_tile_value() != other_object.get_tile_value()) return false;
   if (object.get_collision_velocity_x() != other_object.get_collision_velocity_x()) return false;
   if (object.get_collision_velocity_y() != other_object.get_collision_velocity_y()) return false;
   if (object.get_stopped_by_this_collision() != other_object.get_stopped_by_this_collision()) return false;
   if (object.get_event() != other_object.get_event()) return false;

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
       << (object.get_stopped_by_this_collision() ? "true" : "false")
       << ", "
       << object.build_event_name(object.get_event())
       << ", "
       << object.build_collided_block_edge_name(object.get_collided_against_block_edge())
       << ")";
}


}


