#pragma once


#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class Snap : public AllegroFlare::CameraControlStrategies2D::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/CameraControlStrategies2D/Snap";

      private:
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow;

      protected:


      public:
         Snap();
         virtual ~Snap();

         void set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow);
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* get_entity_to_follow() const;
         virtual void update() override;
      };
   }
}



