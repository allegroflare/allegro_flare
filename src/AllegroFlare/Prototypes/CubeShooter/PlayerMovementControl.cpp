

#include <AllegroFlare/Prototypes/CubeShooter/PlayerMovementControl.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{


PlayerMovementControl::PlayerMovementControl()
   : player_controlled_entity(nullptr)
   , position(nullptr)
   , velocity(nullptr)
   , max_velocity_x(0.06)
   , max_velocity_y(0.045)
   , acceleration(0.008)
   , thruster_max_velocity(0.1)
   , thruster_acceleration_force(0.008)
   , thruster_active(false)
   , moving_up(false)
   , moving_down(false)
   , moving_left(false)
   , moving_right(false)
   , firing_blaster(false)
   , blaster_fired_at(-999)
   , blaster_refire_rate(0.2)
   , blaster_fired_on_last_update(false)
   , max_x(8.0f)
   , min_x(-8.0f)
   , max_y(5.0f)
   , min_y(2.0f)
{
}


PlayerMovementControl::~PlayerMovementControl()
{
}


void PlayerMovementControl::set_thruster_max_velocity(float thruster_max_velocity)
{
   this->thruster_max_velocity = thruster_max_velocity;
}


void PlayerMovementControl::set_thruster_acceleration_force(float thruster_acceleration_force)
{
   this->thruster_acceleration_force = thruster_acceleration_force;
}


void PlayerMovementControl::set_thruster_active(bool thruster_active)
{
   this->thruster_active = thruster_active;
}


void PlayerMovementControl::set_moving_up(bool moving_up)
{
   this->moving_up = moving_up;
}


void PlayerMovementControl::set_moving_down(bool moving_down)
{
   this->moving_down = moving_down;
}


void PlayerMovementControl::set_moving_left(bool moving_left)
{
   this->moving_left = moving_left;
}


void PlayerMovementControl::set_moving_right(bool moving_right)
{
   this->moving_right = moving_right;
}


void PlayerMovementControl::set_firing_blaster(bool firing_blaster)
{
   this->firing_blaster = firing_blaster;
}


void PlayerMovementControl::set_max_x(float max_x)
{
   this->max_x = max_x;
}


void PlayerMovementControl::set_min_x(float min_x)
{
   this->min_x = min_x;
}


void PlayerMovementControl::set_max_y(float max_y)
{
   this->max_y = max_y;
}


void PlayerMovementControl::set_min_y(float min_y)
{
   this->min_y = min_y;
}


float PlayerMovementControl::get_thruster_max_velocity() const
{
   return thruster_max_velocity;
}


float PlayerMovementControl::get_thruster_acceleration_force() const
{
   return thruster_acceleration_force;
}


bool PlayerMovementControl::get_moving_left() const
{
   return moving_left;
}


bool PlayerMovementControl::get_moving_right() const
{
   return moving_right;
}


bool PlayerMovementControl::get_blaster_fired_on_last_update() const
{
   return blaster_fired_on_last_update;
}


float PlayerMovementControl::get_max_x() const
{
   return max_x;
}


float PlayerMovementControl::get_min_x() const
{
   return min_x;
}


float PlayerMovementControl::get_max_y() const
{
   return max_y;
}


float PlayerMovementControl::get_min_y() const
{
   return min_y;
}


void PlayerMovementControl::set_player_controlled_entity(AllegroFlare::Prototypes::CubeShooter::Entity* player_controlled_entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::PlayerMovementControl::set_player_controlled_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::PlayerMovementControl::set_player_controlled_entity]: error: guard \"player_controlled_entity\" not met");
   }
   this->player_controlled_entity = player_controlled_entity;
   position = &player_controlled_entity->get_placement_ref().position;
   velocity = &player_controlled_entity->get_velocity_ref().position;
   return;
}

void PlayerMovementControl::update(float time_now)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::PlayerMovementControl::update]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::PlayerMovementControl::update]: error: guard \"player_controlled_entity\" not met");
   }
   // reset
   blaster_fired_on_last_update = false;

   // update the x/y position movement
   if (moving_up && velocity->y < max_velocity_y && position->y < max_y)
      velocity->y += acceleration;
   if (moving_down && velocity->y > -max_velocity_y && position->y > min_y)
      velocity->y -= acceleration;
   if (moving_left && velocity->x > -max_velocity_x && position->x > min_x)
      velocity->x -= acceleration;
   if (moving_right && velocity->x < max_velocity_x && position->x < max_x)
      velocity->x += acceleration;

   // update the thruster/forward velocity
   if (thruster_active && velocity->z > -thruster_max_velocity)
      velocity->z -= thruster_acceleration_force;

   // update the firing of the blaster
   if (firing_blaster && (time_now - blaster_fired_at > blaster_refire_rate))
   {
      blaster_fired_at = time_now;
      blaster_fired_on_last_update = true;
   } 
   return;
}


} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


