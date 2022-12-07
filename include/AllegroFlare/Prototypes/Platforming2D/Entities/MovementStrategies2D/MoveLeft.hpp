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
               class MoveLeft : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  float speed;

               protected:


               public:
                  MoveLeft(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, float speed=5.0f);
                  ~MoveLeft();

                  void set_speed(float speed);
                  float get_speed() const;
                  void update() override;
               };
            }
         }
      }
   }
}



