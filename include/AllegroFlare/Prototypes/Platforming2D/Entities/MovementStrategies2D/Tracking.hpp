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
               class Tracking : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity;
                  float speed;

               protected:


               public:
                  Tracking(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity=nullptr, float speed=0.5f);
                  ~Tracking();

                  void set_speed(float speed);
                  float get_speed() const;
                  void update() override;
               };
            }
         }
      }
   }
}



