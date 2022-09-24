

#include <Wicked/Entities/MovementStrategies2D/MoveRight.hpp>

#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


MoveRight::MoveRight(Wicked::Entities::Basic2D* entity, float speed)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , speed(speed)
{
}


MoveRight::~MoveRight()
{
}


void MoveRight::set_speed(float speed)
{
   this->speed = speed;
}


float MoveRight::get_speed() const
{
   return speed;
}


void MoveRight::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "MoveRight" << "::" << "update" << ": error: " << "guard \"entity\" not met";
      throw std::runtime_error(error_message.str());
   }
   entity->get_velocity_ref().position = AllegroFlare::vec2d(speed, 0);
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


