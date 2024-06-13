

#include <Wicked/Entities/MovementStrategies2D/HoppingLeft.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


HoppingLeft::HoppingLeft(Wicked::Entities::Basic2D* entity, float jump_force, float speed, float landing_delay)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , jump_force(jump_force)
   , speed(speed)
   , landing_delay(landing_delay)
   , timer(0.0f)
{
}


HoppingLeft::~HoppingLeft()
{
}


void HoppingLeft::set_jump_force(float jump_force)
{
   this->jump_force = jump_force;
}


void HoppingLeft::set_speed(float speed)
{
   this->speed = speed;
}


void HoppingLeft::set_landing_delay(float landing_delay)
{
   this->landing_delay = landing_delay;
}


float HoppingLeft::get_jump_force() const
{
   return jump_force;
}


float HoppingLeft::get_speed() const
{
   return speed;
}


float HoppingLeft::get_landing_delay() const
{
   return landing_delay;
}


void HoppingLeft::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::HoppingLeft::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::HoppingLeft::update]: error: guard \"entity\" not met");
   }
   if (entity->exists("on_ground"))
   {
      entity->get_velocity_ref().position.x = 0;

      timer -= (1.0/60.0f);
      if (timer <= 0)
      {
         timer += landing_delay;
         entity->get_velocity_ref().position.x = 0;
         entity->get_velocity_ref().position.y = -jump_force;
         entity->remove("on_ground");
      }
   }
   else if (!entity->exists("on_ground"))
   {
      entity->get_velocity_ref().position.x = -speed;
   }
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


