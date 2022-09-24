#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <Wicked/Entities/Zones/Base2D.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace Zones
      {
         class Rectangle2D : public Wicked::Entities::Zones::Base2D
         {
         private:
            float x1;
            float y1;
            float x2;
            float y2;

         protected:


         public:
            Rectangle2D(float x1=0.0f, float y1=0.0f, float x2=1.0f, float y2=1.0f);
            virtual ~Rectangle2D();

            float get_x1() const;
            float get_y1() const;
            float get_x2() const;
            float get_y2() const;
            virtual bool collides(AllegroFlare::vec2d point={}) override;
         };
      }
   }
}



