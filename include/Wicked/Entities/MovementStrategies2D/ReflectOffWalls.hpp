#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class ReflectOffWalls : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            float speed;
            bool moving_right;
            bool moving_down;

         protected:


         public:
            ReflectOffWalls(Wicked::Entities::Basic2D* entity=nullptr, float speed=3.0f, bool moving_right=true, bool moving_down=true);
            ~ReflectOffWalls();

            void set_speed(float speed);
            float get_speed() const;
            void update() override;
         };
      }
   }
}



