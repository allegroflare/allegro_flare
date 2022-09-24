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
         class Anchored : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            AllegroFlare::vec2d anchor;

         protected:


         public:
            Anchored(Wicked::Entities::Basic2D* entity=nullptr, AllegroFlare::vec2d anchor={0.0, 0.0});
            ~Anchored();

            void set_anchor(AllegroFlare::vec2d anchor);
            AllegroFlare::vec2d get_anchor() const;
            void update() override;
         };
      }
   }
}



