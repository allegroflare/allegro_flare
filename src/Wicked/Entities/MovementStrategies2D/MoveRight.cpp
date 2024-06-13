

#include <Wicked/Entities/MovementStrategies2D/MoveRight.hpp>

#include <iostream>
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
      error_message << "[Wicked::Entities::MovementStrategies2D::MoveRight::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::MoveRight::update]: error: guard \"entity\" not met");
   }
   entity->get_velocity_ref().position = AllegroFlare::vec2d(speed, 0);
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


