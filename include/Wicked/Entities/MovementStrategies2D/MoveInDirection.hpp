#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class MoveInDirection : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            AllegroFlare::vec2d direction;

         protected:


         public:
            MoveInDirection(Wicked::Entities::Basic2D* entity=nullptr, AllegroFlare::vec2d direction={0.0, 0.0});
            ~MoveInDirection();

            void set_direction(AllegroFlare::vec2d direction);
            AllegroFlare::vec2d get_direction() const;
            void update() override;
         };
      }
   }
}



