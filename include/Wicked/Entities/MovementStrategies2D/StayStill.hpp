#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class StayStill : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;

         protected:


         public:
            StayStill(Wicked::Entities::Basic2D* entity=nullptr);
            ~StayStill();

            void update() override;
         };
      }
   }
}



