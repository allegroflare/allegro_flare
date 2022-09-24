

#include <Wicked/Entities/MovementStrategies2D/Anchored.hpp>

#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


Anchored::Anchored(Wicked::Entities::Basic2D* entity, AllegroFlare::vec2d anchor)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , anchor(anchor)
{
}


Anchored::~Anchored()
{
}


void Anchored::set_anchor(AllegroFlare::vec2d anchor)
{
   this->anchor = anchor;
}


AllegroFlare::vec2d Anchored::get_anchor() const
{
   return anchor;
}


void Anchored::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "Anchored" << "::" << "update" << ": error: " << "guard \"entity\" not met";
      throw std::runtime_error(error_message.str());
   }
   // TODO: this should include a slide, horizontal or otherwise
   entity->get_place_ref().position = anchor;
   entity->get_velocity_ref().position = AllegroFlare::vec2d{0, 0};
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


