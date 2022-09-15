#pragma once


#include <AllegroFlare/Vec3D.hpp>
#include <Wicked/Entities/Zones/Base3D.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace Zones
      {
         class Rectangle3D : public Wicked::Entities::Zones::Base3D
         {
         private:
            float x1;
            float y1;
            float z1;
            float x2;
            float y2;
            float z2;

         protected:


         public:
            Rectangle3D(float x1=0.0f, float y1=0.0f, float z1=0.0f, float x2=1.0f, float y2=1.0f, float z2=1.0f);
            virtual ~Rectangle3D();

            float get_x1() const;
            float get_y1() const;
            float get_z1() const;
            float get_x2() const;
            float get_y2() const;
            float get_z2() const;
            virtual bool collides(AllegroFlare::vec3d point={}) override;
         };
      }
   }
}



