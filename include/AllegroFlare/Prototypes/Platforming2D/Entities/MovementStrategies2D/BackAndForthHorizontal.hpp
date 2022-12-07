#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Base.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            namespace MovementStrategies2D
            {
               class BackAndForthHorizontal : public AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base
               {
               private:
                  AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity;
                  float timer;
                  float travel_speed;
                  float travel_duration;
                  bool direction_of_travel_is_left;

               protected:


               public:
                  BackAndForthHorizontal(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, float travel_speed=4.0f, float travel_duration=4.0f);
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
   }
}



