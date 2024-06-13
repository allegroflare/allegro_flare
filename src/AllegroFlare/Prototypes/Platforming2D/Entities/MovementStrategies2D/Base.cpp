

#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Base.hpp>

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


Base::Base()
{
}


Base::~Base()
{
}


void Base::initialize()
{
   return;
}

void Base::update()
{
   return;
}

void Base::on_collision_update(AllegroFlare::Vec2D previous_place_position, AllegroFlare::Vec2D previous_velocity_position, AllegroFlare::Vec2D new_place_position, AllegroFlare::Vec2D new_velocity_position, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_result, bool top_edge_is_currently_adjacent_to_wall, bool right_edge_is_currently_adjacent_to_wall, bool bottom_edge_is_currently_adjacent_to_wall, bool left_edge_is_currently_adjacent_to_wall)
{
   if (!(collision_step_result))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base::on_collision_update]: error: guard \"collision_step_result\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base::on_collision_update]: error: guard \"collision_step_result\" not met");
   }
   return;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


