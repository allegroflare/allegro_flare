

#include <Wicked/Entities/MovementStrategies2D/FlappingWithRandomness.hpp>

#include <Wicked/EntityFlagNames.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


FlappingWithRandomness::FlappingWithRandomness(Wicked::Entities::Basic2D* entity, float target_elevation)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , target_elevation(target_elevation)
   , flap_strength(1.0f)
   , flap_recovery_rate(0.1f)
   , flap_recovery_counter(1.0f)
   , can_flap(false)
   , random()
{
}


FlappingWithRandomness::~FlappingWithRandomness()
{
}


void FlappingWithRandomness::set_target_elevation(float target_elevation)
{
   this->target_elevation = target_elevation;
}


void FlappingWithRandomness::set_flap_strength(float flap_strength)
{
   this->flap_strength = flap_strength;
}


void FlappingWithRandomness::set_flap_recovery_rate(float flap_recovery_rate)
{
   this->flap_recovery_rate = flap_recovery_rate;
}


float FlappingWithRandomness::get_target_elevation() const
{
   return target_elevation;
}


float FlappingWithRandomness::get_flap_strength() const
{
   return flap_strength;
}


float FlappingWithRandomness::get_flap_recovery_rate() const
{
   return flap_recovery_rate;
}


bool FlappingWithRandomness::get_can_flap() const
{
   return can_flap;
}


void FlappingWithRandomness::set_random_seed(uint32_t random_seed)
{
   random.set_seed(random_seed);
   return;
}

void FlappingWithRandomness::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update]: error: guard \"entity\" not met");
   }
   { // stick horizontal if on floor
      if (entity->exists(ADJACENT_TO_FLOOR)) entity->get_velocity_ref().position.x = 0.0f;
   }

   update_flapability_status();

   bool will_flap = decide_to_flap();
   if (will_flap) flap();
}

void FlappingWithRandomness::flap()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::flap]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::flap]: error: guard \"entity\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::flap]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::flap]: error: guard \"al_is_system_installed()\" not met");
   }
   if (can_flap)
   {
      float x_randomness = random.get_random_float(-0.15, 0.15);
      float y_randomness = random.get_random_float(-1.0, 1.0);
      float flap_recovery_randomness = random.get_random_float(-0.3, 0.3);

      entity->get_velocity_ref().position += AllegroFlare::vec2d{x_randomness, -flap_strength + y_randomness};

      flap_recovery_counter = 1.0f + flap_recovery_randomness;
      can_flap = false;
   }
   return;
}

void FlappingWithRandomness::update_flapability_status()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update_flapability_status]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update_flapability_status]: error: guard \"entity\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update_flapability_status]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::update_flapability_status]: error: guard \"al_is_system_installed()\" not met");
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

bool FlappingWithRandomness::decide_to_flap()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::decide_to_flap]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::decide_to_flap]: error: guard \"entity\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::decide_to_flap]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FlappingWithRandomness::decide_to_flap]: error: guard \"al_is_system_installed()\" not met");
   }
   if (can_flap)
   {
      // decide if entity should skip this flap
      bool skip_occasional_flaps = false;
      if (skip_occasional_flaps)
      {
         bool skip_this_flap = random.get_one_in_chance(3);
         if (skip_this_flap)
         {
            flap_recovery_counter = 0.1;
            can_flap = false;
            return false;
         }
      }

      // flap if on the ground
      {
         if (entity->exists(ADJACENT_TO_FLOOR)) return true;
      }

      // flap if below the target elevation
      {
         float sin_offset_from_target_elevation = sin(al_get_time()) * 16.0f;
         if (entity->get_place_ref().position.y > (target_elevation + sin_offset_from_target_elevation)) return true;
      }
   }
   else
   {
      return false;
   }
   return false;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


