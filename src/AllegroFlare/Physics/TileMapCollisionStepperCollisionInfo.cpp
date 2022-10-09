

#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>




namespace AllegroFlare
{
namespace Physics
{


TileMapCollisionStepperCollisionInfo::TileMapCollisionStepperCollisionInfo(AllegroFlare::Physics::Int2D collided_tile_coordinate, int tile_value, float collision_velocity_x, float collision_velocity_y, bool stopped_by_this_collision, int event)
   : collided_tile_coordinate(collided_tile_coordinate)
   , tile_value(tile_value)
   , collision_velocity_x(collision_velocity_x)
   , collision_velocity_y(collision_velocity_y)
   , stopped_by_this_collision(stopped_by_this_collision)
   , event(event)
{
}


TileMapCollisionStepperCollisionInfo::~TileMapCollisionStepperCollisionInfo()
{
}


void TileMapCollisionStepperCollisionInfo::set_collided_tile_coordinate(AllegroFlare::Physics::Int2D collided_tile_coordinate)
{
   this->collided_tile_coordinate = collided_tile_coordinate;
}


void TileMapCollisionStepperCollisionInfo::set_tile_value(int tile_value)
{
   this->tile_value = tile_value;
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


void TileMapCollisionStepperCollisionInfo::set_event(int event)
{
   this->event = event;
}


AllegroFlare::Physics::Int2D TileMapCollisionStepperCollisionInfo::get_collided_tile_coordinate() const
{
   return collided_tile_coordinate;
}


int TileMapCollisionStepperCollisionInfo::get_tile_value() const
{
   return tile_value;
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


int TileMapCollisionStepperCollisionInfo::get_event() const
{
   return event;
}




} // namespace Physics
} // namespace AllegroFlare


