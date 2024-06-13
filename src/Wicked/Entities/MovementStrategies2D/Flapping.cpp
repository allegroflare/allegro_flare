

#include <Wicked/Entities/MovementStrategies2D/Flapping.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


Flapping::Flapping(Wicked::Entities::Basic2D* entity, float target_elevation)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , target_elevation(target_elevation)
   , flap_strength(1.0f)
   , flap_recovery_rate(0.1f)
   , flap_recovery_counter(1.0f)
   , can_flap(false)
{
}


Flapping::~Flapping()
{
}


void Flapping::set_target_elevation(float target_elevation)
{
   this->target_elevation = target_elevation;
}


void Flapping::set_flap_strength(float flap_strength)
{
   this->flap_strength = flap_strength;
}


void Flapping::set_flap_recovery_rate(float flap_recovery_rate)
{
   this->flap_recovery_rate = flap_recovery_rate;
}


float Flapping::get_target_elevation() const
{
   return target_elevation;
}


float Flapping::get_flap_strength() const
{
   return flap_strength;
}


float Flapping::get_flap_recovery_rate() const
{
   return flap_recovery_rate;
}


bool Flapping::get_can_flap() const
{
   return can_flap;
}


void Flapping::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Flapping::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Flapping::update]: error: guard \"entity\" not met");
   }
   update_flapability_status();

   bool will_flap = decide_to_flap();

   if (will_flap)
   {
      flap();
   }
   // TODO: this should include a slide, horizontal or otherwise
   //entity->get_place_ref().position = anchor;
   //entity->get_velocity_ref().position = AllegroFlare::vec2d{0, 0};
}

void Flapping::update_flapability_status()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Flapping::update_flapability_status]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Flapping::update_flapability_status]: error: guard \"entity\" not met");
   }
   if (!can_flap)
   {
      flap_recovery_counter -= flap_recovery_rate;
      if (flap_recovery_counter <= 0.0f)
      {
         can_flap = true;
         flap_recovery_counter = 0.0f;
      }
   }
}

bool Flapping::decide_to_flap()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Flapping::decide_to_flap]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Flapping::decide_to_flap]: error: guard \"entity\" not met");
   }
   if (can_flap)
   {
      if (entity->get_place_ref().position.y > target_elevation) return true;
   }
   else
   {
      return false;
   }
   return false;
}

void Flapping::flap()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Flapping::flap]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Flapping::flap]: error: guard \"entity\" not met");
   }
   if (can_flap)
   {
      entity->get_velocity_ref().position += AllegroFlare::vec2d{0, -flap_strength};
      flap_recovery_counter = 1.0f;
      can_flap = false;
   }
   return;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


