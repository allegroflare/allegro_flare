#pragma once


#include <Wicked/Entities/Basic3D.hpp>
#include <Wicked/Entities/Zones/Base3D.hpp>
#include <utility>
#include <vector>


namespace Wicked
{
   namespace Physics
   {
      class EntityZoneCollisionObserver
      {
      private:
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> collisions_at_start;
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> collisions_at_end;

      protected:


      public:
         EntityZoneCollisionObserver();
         ~EntityZoneCollisionObserver();

         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> get_collisions_at_start() const;
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> get_collisions_at_end() const;
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> get_collided(std::vector<Wicked::Entities::Basic3D*> entities={}, std::vector<Wicked::Entities::Zones::Base3D*> zones={});
         bool collides(Wicked::Entities::Basic3D* entity=nullptr, Wicked::Entities::Zones::Base3D* zone=nullptr);
         void observe_start_state(std::vector<Wicked::Entities::Basic3D*> entities={}, std::vector<Wicked::Entities::Zones::Base3D*> zones={});
         void observe_end_state(std::vector<Wicked::Entities::Basic3D*> entities={}, std::vector<Wicked::Entities::Zones::Base3D*> zones={});
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> collisions_added();
         std::vector<std::pair<Wicked::Entities::Basic3D*, Wicked::Entities::Zones::Base3D*>> collisions_removed();
      };
   }
}



