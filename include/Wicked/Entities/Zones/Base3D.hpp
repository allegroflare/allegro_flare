#pragma once


#include <AllegroFlare/Vec3D.hpp>
#include <Wicked/Entities/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace Zones
      {
         class Base3D : public Wicked::Entities::Base
         {
         private:

         protected:


         public:
            Base3D();
            virtual ~Base3D();

            virtual bool collides(AllegroFlare::vec3d point={});
         };
      }
   }
}



