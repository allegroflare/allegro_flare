

#include <Wicked/Entities/MovementStrategies2D/ReflectOffWalls.hpp>

#include <Wicked/EntityFlagNames.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


ReflectOffWalls::ReflectOffWalls(Wicked::Entities::Basic2D* entity, float speed, bool moving_right, bool moving_down)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , speed(speed)
   , moving_right(moving_right)
   , moving_down(moving_down)
{
}


ReflectOffWalls::~ReflectOffWalls()
{
}


void ReflectOffWalls::set_speed(float speed)
{
   this->speed = speed;
}


float ReflectOffWalls::get_speed() const
{
   return speed;
}


void ReflectOffWalls::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::ReflectOffWalls::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::ReflectOffWalls::update]: error: guard \"entity\" not met");
   }
   AllegroFlare::vec2d velocity_position;

   // vertical
   if (moving_down && entity->exists(ADJACENT_TO_FLOOR)) 
   {
      moving_down = false;
   }
   else if (!moving_down && entity->exists(ADJACENT_TO_CEILING)) 
   {
      moving_down = true;
   }

   if (moving_down) velocity_position.y = 1.0f;
   else velocity_position.y = -1.0f;

   // horizgonal
   if (moving_right && entity->exists(ADJACENT_TO_RIGHT_WALL)) 
   {
      moving_right = false;
   }
   else if (!moving_right && entity->exists(ADJACENT_TO_LEFT_WALL)) 
   {
      moving_right = true;
   }

   if (moving_right) velocity_position.x = 1.0f;
   else velocity_position.x = -1.0f;

   entity->get_velocity_ref().position = velocity_position;
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


