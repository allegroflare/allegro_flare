

#include <Wicked/Entities/MovementStrategies2D/MoveInDirection.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


MoveInDirection::MoveInDirection(Wicked::Entities::Basic2D* entity, AllegroFlare::vec2d direction)
   : Wicked::Entities::MovementStrategies2D::Base()
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
      error_message << "[Wicked::Entities::MovementStrategies2D::MoveInDirection::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::MoveInDirection::update]: error: guard \"entity\" not met");
   }
   entity->get_velocity_ref().position = direction;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


