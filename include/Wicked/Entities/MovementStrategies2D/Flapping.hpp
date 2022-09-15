#pragma once


#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/Base.hpp>


namespace Wicked
{
   namespace Entities
   {
      namespace MovementStrategies2D
      {
         class Flapping : public Wicked::Entities::MovementStrategies2D::Base
         {
         private:
            Wicked::Entities::Basic2D* entity;
            float target_elevation;
            float flap_strength;
            float flap_recovery_rate;
            float flap_recovery_counter;
            bool can_flap;
            void update_flapability_status();
            bool decide_to_flap();

         protected:


         public:
            Flapping(Wicked::Entities::Basic2D* entity=nullptr, float target_elevation=0.0f);
            ~Flapping();

            void set_target_elevation(float target_elevation);
            void set_flap_strength(float flap_strength);
            void set_flap_recovery_rate(float flap_recovery_rate);
            float get_target_elevation() const;
            float get_flap_strength() const;
            float get_flap_recovery_rate() const;
            bool get_can_flap() const;
            void update() override;
            void flap();
         };
      }
   }
}



