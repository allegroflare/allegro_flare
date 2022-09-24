#pragma once


#include <AllegroFlare/Placement3D.hpp>
#include <Wicked/Entities/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      class Basic3D : public Wicked::Entities::Base
      {
      private:
         AllegroFlare::Placement3D place;
         AllegroFlare::Placement3D velocity;

      protected:


      public:
         Basic3D();
         ~Basic3D();

         void set_place(AllegroFlare::Placement3D place);
         void set_velocity(AllegroFlare::Placement3D velocity);
         AllegroFlare::Placement3D get_place() const;
         AllegroFlare::Placement3D get_velocity() const;
         AllegroFlare::Placement3D &get_place_ref();
         AllegroFlare::Placement3D &get_velocity_ref();
         void TODO();
      };
   }
}



