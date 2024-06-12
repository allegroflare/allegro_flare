

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/MoveInDirection.hpp>

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


MoveInDirection::MoveInDirection(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, AllegroFlare::vec2d direction)
   : AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , direction(direction)
{
}


MoveInDirection::~MoveInDirection()
{
}


void MoveInDirection::set_direction(AllegroFlare::vec2d direction)
{
   this->direction = direction;
}


AllegroFlare::vec2d MoveInDirection::get_direction() const
{
   return direction;
}


void MoveInDirection::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveInDirection::update]: error: guard \"entity\" not met");
   }
   entity->get_velocity_ref().position = direction;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


