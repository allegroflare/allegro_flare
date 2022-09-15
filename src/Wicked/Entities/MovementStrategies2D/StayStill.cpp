

#include <Wicked/Entities/MovementStrategies2D/StayStill.hpp>

#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


StayStill::StayStill(Wicked::Entities::Basic2D* entity)
   : Wicked::Entities::MovementStrategies2D::Base()
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
      error_message << "StayStill" << "::" << "update" << ": error: " << "guard \"entity\" not met";
      throw std::runtime_error(error_message.str());
   }
   entity->get_velocity_ref().position = AllegroFlare::vec2d(0, 0);
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


