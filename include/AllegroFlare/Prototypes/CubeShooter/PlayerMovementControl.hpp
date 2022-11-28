#pragma once


#include <AllegroFlare/Prototypes/CubeShooter/Entity.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         class PlayerMovementControl
         {
         private:
            AllegroFlare::Prototypes::CubeShooter::Entity* player_controlled_entity;
            AllegroFlare::Vec3D* position;
            AllegroFlare::Vec3D* velocity;
            float max_velocity_x;
            float max_velocity_y;
            float acceleration;
            float thruster_max_velocity;
            float thruster_acceleration_force;
            bool thruster_active;
            bool moving_up;
            bool moving_down;
            bool moving_left;
            bool moving_right;
            bool firing_blaster;
            float blaster_fired_at;
            float blaster_refire_rate;
            bool blaster_fired_on_last_update;
            float max_x;
            float min_x;
            float max_y;
            float min_y;

         protected:


         public:
            PlayerMovementControl();
            ~PlayerMovementControl();

            void set_thruster_max_velocity(float thruster_max_velocity);
            void set_thruster_acceleration_force(float thruster_acceleration_force);
            void set_thruster_active(bool thruster_active);
            void set_moving_up(bool moving_up);
            void set_moving_down(bool moving_down);
            void set_moving_left(bool moving_left);
            void set_moving_right(bool moving_right);
            void set_firing_blaster(bool firing_blaster);
            void set_max_x(float max_x);
            void set_min_x(float min_x);
            void set_max_y(float max_y);
            void set_min_y(float min_y);
            float get_thruster_max_velocity() const;
            float get_thruster_acceleration_force() const;
            bool get_moving_left() const;
            bool get_moving_right() const;
            bool get_blaster_fired_on_last_update() const;
            float get_max_x() const;
            float get_min_x() const;
            float get_max_y() const;
            float get_min_y() const;
            void set_player_controlled_entity(AllegroFlare::Prototypes::CubeShooter::Entity* player_controlled_entity=nullptr);
            void update(float time_now=0);
         };
      }
   }
}



