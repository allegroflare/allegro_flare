#pragma once


#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class SmoothSnapWithZoomEffect : public AllegroFlare::CameraControlStrategies2D::Base
      {
      public:
         static constexpr char* TYPE = "AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect";

      private:
         float room_width;
         float room_height;
         Wicked::Entities::Basic2D* entity_to_follow;

      protected:


      public:
         SmoothSnapWithZoomEffect(float room_width=1.0f, float room_height=1.0f);
         virtual ~SmoothSnapWithZoomEffect();

         void set_entity_to_follow(Wicked::Entities::Basic2D* entity_to_follow);
         Wicked::Entities::Basic2D* get_entity_to_follow() const;
         virtual void initialize() override;
         virtual void update() override;
      };
   }
}



