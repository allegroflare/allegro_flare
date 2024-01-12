#pragma once


#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class HorizontalRail : public AllegroFlare::CameraControlStrategies2D::Base
      {
      public:
         static constexpr char* TYPE = (char*)"CameraControlStrategies2D/HorizontalRail";

      private:
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow;
         float tracking_target_position_x;
         float tracking_target_position_y;

      protected:


      public:
         HorizontalRail();
         virtual ~HorizontalRail();

         void set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow);
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* get_entity_to_follow() const;
         virtual void initialize() override;
         virtual void update() override;
      };
   }
}



