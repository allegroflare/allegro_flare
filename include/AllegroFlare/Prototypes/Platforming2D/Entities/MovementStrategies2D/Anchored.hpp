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
               class Anchored : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  AllegroFlare::vec2d anchor;

               protected:


               public:
                  Anchored(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, AllegroFlare::vec2d anchor={0.0, 0.0});
                  ~Anchored();

                  void set_anchor(AllegroFlare::vec2d anchor);
                  AllegroFlare::vec2d get_anchor() const;
                  void update() override;
               };
            }
         }
      }
   }
}



