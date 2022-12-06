#pragma once


#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class SmoothSnap : public AllegroFlare::CameraControlStrategies2D::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/CameraControlStrategies2D/SmoothSnap";

      private:
         float room_width;
         float room_height;
         Wicked::Entities::Basic2D* entity_to_follow;

      protected:


      public:
         SmoothSnap(float room_width=1.0f, float room_height=1.0f);
         virtual ~SmoothSnap();

         void set_entity_to_follow(Wicked::Entities::Basic2D* entity_to_follow);
         Wicked::Entities::Basic2D* get_entity_to_follow() const;
         virtual void initialize() override;
         virtual void update() override;
      };
   }
}



