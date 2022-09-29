

#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>




namespace AllegroFlare
{
namespace Physics
{


TileMapCollisionStepperCollisionInfo::TileMapCollisionStepperCollisionInfo(AllegroFlare::Physics::Int2D collided_tile_coordinate, float collision_velocity_x, float collision_velocity_y, bool stopped_by_this_collision)
   : collided_tile_coordinate(collided_tile_coordinate)
   , collision_velocity_x(collision_velocity_x)
   , collision_velocity_y(collision_velocity_y)
   , stopped_by_this_collision(stopped_by_this_collision)
{
}


TileMapCollisionStepperCollisionInfo::~TileMapCollisionStepperCollisionInfo()
{
}


void TileMapCollisionStepperCollisionInfo::set_collided_tile_coordinate(AllegroFlare::Physics::Int2D collided_tile_coordinate)
{
   this->collided_tile_coordinate = collided_tile_coordinate;
}


void TileMapCollisionStepperCollisionInfo::set_collision_velocity_x(float collision_velocity_x)
{
   this->collision_velocity_x = collision_velocity_x;
}


void TileMapCollisionStepperCollisionInfo::set_collision_velocity_y(float collision_velocity_y)
{
   this->collision_velocity_y = collision_velocity_y;
}


void TileMapCollisionStepperCollisionInfo::set_stopped_by_this_collision(bool stopped_by_this_collision)
{
   this->stopped_by_this_collision = stopped_by_this_collision;
}


AllegroFlare::Physics::Int2D TileMapCollisionStepperCollisionInfo::get_collided_tile_coordinate() const
{
   return collided_tile_coordinate;
}


float TileMapCollisionStepperCollisionInfo::get_collision_velocity_x() const
{
   return collision_velocity_x;
}


float TileMapCollisionStepperCollisionInfo::get_collision_velocity_y() const
{
   return collision_velocity_y;
}


bool TileMapCollisionStepperCollisionInfo::get_stopped_by_this_collision() const
{
   return stopped_by_this_collision;
}




} // namespace Physics
} // namespace AllegroFlare


