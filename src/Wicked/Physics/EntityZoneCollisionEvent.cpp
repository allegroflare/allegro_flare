

#include <Wicked/Physics/EntityZoneCollisionEvent.hpp>




namespace Wicked
{
namespace Physics
{


EntityZoneCollisionEvent::EntityZoneCollisionEvent(int zone_id, Wicked::Entity* entity, Wicked::Physics::zone_collision_event_t event_type)
   : zone_id(zone_id)
   , entity(entity)
   , event_type(event_type)
{
}


EntityZoneCollisionEvent::~EntityZoneCollisionEvent()
{
}


int EntityZoneCollisionEvent::get_zone_id() const
{
   return zone_id;
}


Wicked::Entity* EntityZoneCollisionEvent::get_entity() const
{
   return entity;
}


Wicked::Physics::zone_collision_event_t EntityZoneCollisionEvent::get_event_type() const
{
   return event_type;
}




} // namespace Physics
} // namespace Wicked


