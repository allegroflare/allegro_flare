

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
   , collided_against_block_edge(CollidingBlockEdge::EDGE_UNDEFINED)
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


void TileMapCollisionStepperCollisionInfo::set_collided_against_block_edge(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge collided_against_block_edge)
{
   this->collided_against_block_edge = collided_against_block_edge;
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


AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge TileMapCollisionStepperCollisionInfo::get_collided_against_block_edge() const
{
   return collided_against_block_edge;
}


bool TileMapCollisionStepperCollisionInfo::is_tile_value(int tile_value)
{
   return this->tile_value == tile_value;
}

bool TileMapCollisionStepperCollisionInfo::is_event(int event)
{
   return this->event == event;
}

std::string TileMapCollisionStepperCollisionInfo::build_event_name(int event)
{
   switch(event)
   {
      case EVENT_UNDEFINED:
         return "undefined";
      break;

      case EVENT_ENTERED:
         return "entered";
      break;

      case EVENT_EXITED:
         return "exited";
      break;

      case EVENT_COLLIDED_AGAINST:
         return "collided_against";
      break;

      case EVENT_STAYED_ON:
         return "stayed_on";
      break;
   }
   return "[build_event_name-error_value]";
}

std::string TileMapCollisionStepperCollisionInfo::build_collided_block_edge_name(AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo::CollidingBlockEdge event)
{
   switch(event)
   {
      case EDGE_UNDEFINED:
         return "undefined_edge";
      break;

      case EDGE_TOP:
         return "top_edge";
      break;

      case EDGE_RIGHT:
         return "right_edge";
      break;

      case EDGE_BOTTOM:
         return "bottom_edge";
      break;

      case EDGE_LEFT:
         return "left_edge";
      break;
   }
   return "[build_collided_block_edge_name_name-error_value]";
}


} // namespace Physics
} // namespace AllegroFlare


