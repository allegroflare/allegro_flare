

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Tracking.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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


Tracking::Tracking(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity, float speed)
   : AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base()
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking::update]: error: guard \"entity\" not met");
   }
   if (!(tracked_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking::update]: error: guard \"tracked_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking::update]: error: guard \"tracked_entity\" not met");
   }
   AllegroFlare::vec2d entity_position = entity->get_place_ref().position;
   AllegroFlare::vec2d tracked_entity_position = tracked_entity->get_place_ref().position;

   AllegroFlare::vec2d direction_vector = (tracked_entity_position - entity_position).normalized();
   direction_vector *= speed;

   entity->get_velocity_ref().position = direction_vector;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


