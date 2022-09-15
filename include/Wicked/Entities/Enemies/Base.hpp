#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace Enemies
      {
         class Base : public Wicked::Entities::Basic2D
         {
         private:
            Wicked::Entities::MovementStrategies2D::Base* movement_strategy;

         protected:


         public:
            Base();
            virtual ~Base();

            void set_movement_strategy(Wicked::Entities::MovementStrategies2D::Base* movement_strategy);
            Wicked::Entities::MovementStrategies2D::Base* get_movement_strategy() const;
            virtual void update() override;
            virtual void draw() override;
         };
      }
   }
}



