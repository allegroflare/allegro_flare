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
            namespace Enemies
            {
               class Base : public AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy;

               protected:


               public:
                  Base();
                  virtual ~Base();

                  void set_movement_strategy(AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy);
                  AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* get_movement_strategy() const;
                  virtual void update() override;
                  virtual void draw() override;
               };
            }
         }
      }
   }
}



