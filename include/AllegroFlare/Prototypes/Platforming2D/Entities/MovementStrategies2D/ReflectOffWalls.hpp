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
               class ReflectOffWalls : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  float speed;
                  bool moving_right;
                  bool moving_down;

               protected:


               public:
                  ReflectOffWalls(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, float speed=3.0f, bool moving_right=true, bool moving_down=true);
                  ~ReflectOffWalls();

                  void set_speed(float speed);
                  float get_speed() const;
                  void update() override;
               };
            }
         }
      }
   }
}



