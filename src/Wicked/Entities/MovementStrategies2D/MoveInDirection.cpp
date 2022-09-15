

#include <Wicked/Entities/MovementStrategies2D/MoveInDirection.hpp>

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
      error_message << "MoveInDirection" << "::" << "update" << ": error: " << "guard \"entity\" not met";
      throw std::runtime_error(error_message.str());
   }
   entity->get_velocity_ref().position = direction;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


