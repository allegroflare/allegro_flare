#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class Tracking : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            Wicked::Entities::Basic2D* tracked_entity;
            float speed;

         protected:


         public:
            Tracking(Wicked::Entities::Basic2D* entity=nullptr, Wicked::Entities::Basic2D* tracked_entity=nullptr, float speed=0.5f);
            ~Tracking();

            void set_speed(float speed);
            float get_speed() const;
            void update() override;
         };
      }
   }
}



