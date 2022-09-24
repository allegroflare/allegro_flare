#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <Wicked/Entities/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace Zones
      {
         class Base2D : public Wicked::Entities::Base
         {
         private:

         protected:


         public:
            Base2D();
            virtual ~Base2D();

            virtual bool collides(AllegroFlare::vec2d point={});
         };
      }
   }
}



