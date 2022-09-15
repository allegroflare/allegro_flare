#pragma once


#include <Wicked/Entity.hpp>
#include <Wicked/Physics/ZoneCollisionEventEnum.hpp>


namespace Wicked
{
   namespace Physics
   {
      class EntityZoneCollisionEvent
      {
      private:
         int zone_id;
         Wicked::Entity* entity;
         Wicked::Physics::zone_collision_event_t event_type;

      protected:


      public:
         EntityZoneCollisionEvent(int zone_id=-1, Wicked::Entity* entity=nullptr, Wicked::Physics::zone_collision_event_t event_type=Wicked::Physics::COLLISION_EVENT_NONE);
         ~EntityZoneCollisionEvent();

         int get_zone_id() const;
         Wicked::Entity* get_entity() const;
         Wicked::Physics::zone_collision_event_t get_event_type() const;
      };
   }
}



