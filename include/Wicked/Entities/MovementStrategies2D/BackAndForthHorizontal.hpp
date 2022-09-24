#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class BackAndForthHorizontal : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            float timer;
            float travel_speed;
            float travel_duration;
            bool direction_of_travel_is_left;

         protected:


         public:
            BackAndForthHorizontal(Wicked::Entities::Basic2D* entity=nullptr, float travel_speed=4.0f, float travel_duration=4.0f);
            ~BackAndForthHorizontal();

            void set_travel_speed(float travel_speed);
            void set_travel_duration(float travel_duration);
            float get_travel_speed() const;
            float get_travel_duration() const;
            void update() override;
         };
      }
   }
}



