

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Anchored.hpp>

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


Anchored::Anchored(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, AllegroFlare::vec2d anchor)
   : AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base()
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Anchored::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Anchored::update]: error: guard \"entity\" not met");
   }
   // TODO: this should include a slide, horizontal or otherwise
   entity->get_place_ref().position = anchor;
   entity->get_velocity_ref().position = AllegroFlare::vec2d{0, 0};
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


