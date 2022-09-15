#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class FallOnTrackingRange : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            Wicked::Entities::Basic2D* tracked_entity;
            float range_radius;
            bool triggered;

         protected:


         public:
            FallOnTrackingRange(Wicked::Entities::Basic2D* entity=nullptr, Wicked::Entities::Basic2D* tracked_entity=nullptr, float range_radius=72.0f);
            ~FallOnTrackingRange();

            void set_range_radius(float range_radius);
            float get_range_radius() const;
            bool get_triggered() const;
            void update() override;
         };
      }
   }
}



