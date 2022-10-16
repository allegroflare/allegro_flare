

#include <AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect.hpp>

#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CameraControlStrategies2D
{


SmoothSnapWithZoomEffect::SmoothSnapWithZoomEffect(float room_width, float room_height)
   : AllegroFlare::CameraControlStrategies2D::Base(AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::TYPE)
   , room_width(room_width)
   , room_height(room_height)
   , entity_to_follow(nullptr)
{
}


SmoothSnapWithZoomEffect::~SmoothSnapWithZoomEffect()
{
}


void SmoothSnapWithZoomEffect::set_entity_to_follow(Wicked::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


Wicked::Entities::Basic2D* SmoothSnapWithZoomEffect::get_entity_to_follow() const
{
   return entity_to_follow;
}


void SmoothSnapWithZoomEffect::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "SmoothSnapWithZoomEffect" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "SmoothSnapWithZoomEffect" << "::" << "initialize" << ": error: " << "guard \"get_camera()\" not met";
      throw std::runtime_error(error_message.str());
   }
   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   get_camera_ref()->position = {room_width/2, room_height/2};

   Base::initialize();
   return;
}

void SmoothSnapWithZoomEffect::update()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "SmoothSnapWithZoomEffect" << "::" << "update" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "SmoothSnapWithZoomEffect" << "::" << "update" << ": error: " << "guard \"get_camera()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(entity_to_follow))
   {
      std::stringstream error_message;
      error_message << "SmoothSnapWithZoomEffect" << "::" << "update" << ": error: " << "guard \"entity_to_follow\" not met";
      throw std::runtime_error(error_message.str());
   }
   int room_x = (entity_to_follow->get_place_ref().position.x / room_width);
   int room_y = (entity_to_follow->get_place_ref().position.y / room_height);
   AllegroFlare::vec2d target = {room_width/2, room_height/2};
   target += AllegroFlare::vec2d(room_x * room_width, room_y * room_height);

   AllegroFlare::vec2d position = get_camera_ref()->position;

   AllegroFlare::vec2d delta = target - position;

   if (delta == AllegroFlare::Vec2D(0.0, 0.0))
   {
      // no zoom effect
   }
   else
   {
      // TODO: work out some fun here
   }

   get_camera_ref()->position += (delta * 0.1);

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


