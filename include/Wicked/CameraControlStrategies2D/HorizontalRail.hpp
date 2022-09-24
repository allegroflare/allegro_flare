#pragma once


#include <Wicked/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>


namespace Wicked
{
   namespace CameraControlStrategies2D
   {
      class HorizontalRail : public Wicked::CameraControlStrategies2D::Base
      {
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



