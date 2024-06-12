

#include <Wicked/Entities/MovementStrategies2D/FallOnTrackingRange.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{
namespace MovementStrategies2D
{


FallOnTrackingRange::FallOnTrackingRange(Wicked::Entities::Basic2D* entity, Wicked::Entities::Basic2D* tracked_entity, float range_radius)
   : Wicked::Entities::MovementStrategies2D::Base()
   , entity(entity)
   , tracked_entity(tracked_entity)
   , range_radius(range_radius)
   , triggered(false)
{
}


FallOnTrackingRange::~FallOnTrackingRange()
{
}


void FallOnTrackingRange::set_range_radius(float range_radius)
{
   this->range_radius = range_radius;
}


float FallOnTrackingRange::get_range_radius() const
{
   return range_radius;
}


bool FallOnTrackingRange::get_triggered() const
{
   return triggered;
}


void FallOnTrackingRange::update()
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FallOnTrackingRange::update]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FallOnTrackingRange::update]: error: guard \"entity\" not met");
   }
   if (!(tracked_entity))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::MovementStrategies2D::FallOnTrackingRange::update]: error: guard \"tracked_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::MovementStrategies2D::FallOnTrackingRange::update]: error: guard \"tracked_entity\" not met");
   }
   if (!triggered)
   {
      AllegroFlare::vec2d entity_position = entity->get_place_ref().position;
      AllegroFlare::vec2d tracked_entity_position = tracked_entity->get_place_ref().position;

      float padding = 8;
      float tracked_entity_x = tracked_entity->get_place_ref().position.x;
      float tracked_entity_y = tracked_entity->get_place_ref().position.y;
      if (entity->get_place_ref().in_range(tracked_entity_x, tracked_entity_y, range_radius))
      {
         triggered = true;
      }

      if (!triggered)
      {
         entity->get_velocity_ref().position = AllegroFlare::vec2d{0, 0};
      }
      //if (entity_position)
   }
}


} // namespace MovementStrategies2D
} // namespace Entities
} // namespace Wicked


