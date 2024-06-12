

#include <Wicked/Physics/EntityZoneCollisionObserver.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Physics
{


EntityZoneCollisionObserver::EntityZoneCollisionObserver()
   : collisions_at_start({})
   , collisions_at_end({})
{
}


EntityZoneCollisionObserver::~EntityZoneCollisionObserver()
{
}


std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> EntityZoneCollisionObserver::get_collisions_at_start() const
{
   return collisions_at_start;
}


std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> EntityZoneCollisionObserver::get_collisions_at_end() const
{
   return collisions_at_end;
}


std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> EntityZoneCollisionObserver::get_collided(std::vector<Wicked::Entities::Basic3D*> entities, std::vector<Wicked::Entities::Zones::Base3D*> zones)
{
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> result;

   for (auto &entity : entities)
   {
      for (auto &zone : zones)
      {
         if (collides(entity, zone)) result.push_back({ entity, zone });
      }
   }

   return result;
}

bool EntityZoneCollisionObserver::collides(Wicked::Entities::Basic3D* entity, Wicked::Entities::Zones::Base3D* zone)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Physics::EntityZoneCollisionObserver::collides]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Physics::EntityZoneCollisionObserver::collides]: error: guard \"entity\" not met");
   }
   if (!(zone))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Physics::EntityZoneCollisionObserver::collides]: error: guard \"zone\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Physics::EntityZoneCollisionObserver::collides]: error: guard \"zone\" not met");
   }
   // TODO: make different supported types for collision
   return (zone->collides(entity->get_place_ref().position));
}

void EntityZoneCollisionObserver::observe_start_state(std::vector<Wicked::Entities::Basic3D*> entities, std::vector<Wicked::Entities::Zones::Base3D*> zones)
{
   collisions_at_start = get_collided(entities, zones);
   return;
}

void EntityZoneCollisionObserver::observe_end_state(std::vector<Wicked::Entities::Basic3D*> entities, std::vector<Wicked::Entities::Zones::Base3D*> zones)
{
   collisions_at_end = get_collided(entities, zones);
   return;
}

std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> EntityZoneCollisionObserver::collisions_added()
{
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> diff;

   std::set_difference(
     collisions_at_end.begin(), collisions_at_end.end(),
     collisions_at_start.begin(), collisions_at_start.end(),
     std::inserter(diff, diff.begin())
   );

   return diff;
}

std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> EntityZoneCollisionObserver::collisions_removed()
{
   std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> diff;

   std::set_difference(
     collisions_at_start.begin(), collisions_at_start.end(),
     collisions_at_end.begin(), collisions_at_end.end(),
     std::inserter(diff, diff.begin())
   );

   return diff;
}


} // namespace Physics
} // namespace Wicked


