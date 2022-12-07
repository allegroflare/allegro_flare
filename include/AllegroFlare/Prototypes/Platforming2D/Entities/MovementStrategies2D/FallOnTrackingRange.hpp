#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Base.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            namespace MovementStrategies2D
            {
               class FallOnTrackingRange : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity;
                  float range_radius;
                  bool triggered;

               protected:


               public:
                  FallOnTrackingRange(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity=nullptr, float range_radius=72.0f);
                  ~FallOnTrackingRange();

                  void set_range_radius(float range_radius);
                  float get_range_radius() const;
                  bool get_triggered() const;
                  void update() override;
               };
            }
         }
      }
   }
}



