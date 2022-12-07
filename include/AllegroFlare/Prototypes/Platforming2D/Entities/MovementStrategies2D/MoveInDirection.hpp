#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Base.hpp>
#include <AllegroFlare/Vec2D.hpp>


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
               class MoveInDirection : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  AllegroFlare::vec2d direction;

               protected:


               public:
                  MoveInDirection(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, AllegroFlare::vec2d direction={0.0, 0.0});
                  ~MoveInDirection();

                  void set_direction(AllegroFlare::vec2d direction);
                  AllegroFlare::vec2d get_direction() const;
                  void update() override;
               };
            }
         }
      }
   }
}



