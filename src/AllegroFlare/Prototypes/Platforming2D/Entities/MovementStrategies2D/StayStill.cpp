

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/StayStill.hpp>

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


StayStill::StayStill(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
   : AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base()
   , entity(entity)
{
}


StayStill::~StayStill()
{
}


void StayStill::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::StayStill::update]: error: guard \"entity\" not met");
   }
   entity->get_velocity_ref().position = AllegroFlare::vec2d(0, 0);
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


