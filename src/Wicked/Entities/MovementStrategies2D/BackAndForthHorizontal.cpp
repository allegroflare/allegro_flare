

#include <Wicked/Entities/MovementStrategies2D/BackAndForthHorizontal.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


BackAndForthHorizontal::BackAndForthHorizontal(Wicked::Entities::Basic2D* entity, float travel_speed, float travel_duration)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , timer(0)
   , travel_speed(travel_speed)
   , travel_duration(travel_duration)
   , direction_of_travel_is_left(true)
{
}


BackAndForthHorizontal::~BackAndForthHorizontal()
{
}


void BackAndForthHorizontal::set_travel_speed(float travel_speed)
{
   this->travel_speed = travel_speed;
}


void BackAndForthHorizontal::set_travel_duration(float travel_duration)
{
   this->travel_duration = travel_duration;
}


float BackAndForthHorizontal::get_travel_speed() const
{
   return travel_speed;
}


float BackAndForthHorizontal::get_travel_duration() const
{
   return travel_duration;
}


void BackAndForthHorizontal::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::BackAndForthHorizontal::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::BackAndForthHorizontal::update]: error: guard \"entity\" not met");
   }
   timer -= (1.0/60.0);

   if (timer <= 0.0f)
   {
      timer += travel_duration; 
      direction_of_travel_is_left = !direction_of_travel_is_left;
   }

   if (direction_of_travel_is_left)
   {
      entity->get_velocity_ref().position = AllegroFlare::vec2d(-travel_speed, 0);
   }
   else
   {
      entity->get_velocity_ref().position = AllegroFlare::vec2d(travel_speed, 0);
   }
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


