

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/MoveRight.hpp>

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


MoveRight::MoveRight(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, float speed)
   : AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base()
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveRight::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::MoveRight::update]: error: guard \"entity\" not met");
   }
   entity->get_velocity_ref().position = AllegroFlare::vec2d(speed, 0);
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


