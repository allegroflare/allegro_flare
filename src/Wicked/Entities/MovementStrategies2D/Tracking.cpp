

#include <Wicked/Entities/MovementStrategies2D/Tracking.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


Tracking::Tracking(Wicked::Entities::Basic2D* entity, Wicked::Entities::Basic2D* tracked_entity, float speed)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , tracked_entity(tracked_entity)
   , speed(speed)
{
}


Tracking::~Tracking()
{
}


void Tracking::set_speed(float speed)
{
   this->speed = speed;
}


float Tracking::get_speed() const
{
   return speed;
}


void Tracking::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Tracking::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Tracking::update]: error: guard \"entity\" not met");
   }
   if (!(tracked_entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::Tracking::update]: error: guard \"tracked_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::Tracking::update]: error: guard \"tracked_entity\" not met");
   }
   AllegroFlare::vec2d entity_position = entity->get_place_ref().position;
   AllegroFlare::vec2d tracked_entity_position = tracked_entity->get_place_ref().position;

   AllegroFlare::vec2d direction_vector = (tracked_entity_position - entity_position).normalized();
   direction_vector *= speed;

   entity->get_velocity_ref().position = direction_vector;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


