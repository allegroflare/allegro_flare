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
               class MoveRight : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  float speed;

               protected:


               public:
                  MoveRight(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, float speed=5.0f);
                  ~MoveRight();

                  void set_speed(float speed);
                  float get_speed() const;
                  void update() override;
               };
            }
         }
      }
   }
}



