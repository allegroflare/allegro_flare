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
               class HoppingLeft : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  float jump_force;
                  float speed;
                  float landing_delay;
                  float timer;

               protected:


               public:
                  HoppingLeft(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, float jump_force=5.0f, float speed=1.0f, float landing_delay=2.0f);
                  ~HoppingLeft();

                  void set_jump_force(float jump_force);
                  void set_speed(float speed);
                  void set_landing_delay(float landing_delay);
                  float get_jump_force() const;
                  float get_speed() const;
                  float get_landing_delay() const;
                  void update() override;
               };
            }
         }
      }
   }
}



