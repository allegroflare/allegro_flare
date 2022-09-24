#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class MoveLeft : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            float speed;

         protected:


         public:
            MoveLeft(Wicked::Entities::Basic2D* entity=nullptr, float speed=5.0f);
            ~MoveLeft();

            void set_speed(float speed);
            float get_speed() const;
            void update() override;
         };
      }
   }
}



