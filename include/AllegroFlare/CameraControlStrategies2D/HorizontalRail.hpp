#pragma once


#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class HorizontalRail : public AllegroFlare::CameraControlStrategies2D::Base
      {
      public:
         static constexpr char* TYPE = (char*)"CameraControlStrategies2D/HorizontalRail";

      private:
         Wicked::Entities::Basic2D* entity_to_follow;

      protected:


      public:
         HorizontalRail();
         virtual ~HorizontalRail();

         void set_entity_to_follow(Wicked::Entities::Basic2D* entity_to_follow);
         Wicked::Entities::Basic2D* get_entity_to_follow() const;
         virtual void initialize() override;
         virtual void update() override;
      };
   }
}



