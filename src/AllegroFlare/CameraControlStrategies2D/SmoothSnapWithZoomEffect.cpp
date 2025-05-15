

#include <AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect.hpp>

#include <AllegroFlare/Useful.hpp>
#include <cmath>
#include <iostream>
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
   , tracking_target_position_x(0.0)
   , tracking_target_position_y(0.0)
{
}


SmoothSnapWithZoomEffect::~SmoothSnapWithZoomEffect()
{
}


void SmoothSnapWithZoomEffect::set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* SmoothSnapWithZoomEffect::get_entity_to_follow() const
{
   return entity_to_follow;
}


void SmoothSnapWithZoomEffect::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(!get_initialized())\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"get_camera()\" not met");
   }
   if (!((room_width > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_width > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_width > 0)\" not met");
   }
   if (!((room_height > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_height > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_height > 0)\" not met");
   }
   // TODO: only allow setting "room_width" and "room_height" to positive values

   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   get_camera_ref()->position = AllegroFlare::Vec2D{room_width/2, room_height/2};

   Base::initialize();
   return;
}

void SmoothSnapWithZoomEffect::update()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::update]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::update]: error: guard \"get_initialized()\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::update]: error: guard \"get_camera()\" not met");
   }
   // If the camera loses track of the "entity_to_follow" (the tracking target dies for example), this logic will
   // retain the last coordinate that had been tracked, and use it until a new tracking target is introduced.
   if (entity_to_follow)
   {
      tracking_target_position_x = entity_to_follow->get_place_ref().position.x;
      tracking_target_position_y = entity_to_follow->get_place_ref().position.y;
   }

   int target_room_x = (tracking_target_position_x / room_width);
   int target_room_y = (tracking_target_position_y / room_height);
   AllegroFlare::vec2d target_position = AllegroFlare::Vec2D{room_width/2, room_height/2};
   target_position += AllegroFlare::vec2d(target_room_x * room_width, target_room_y * room_height);

   AllegroFlare::vec2d current_camera_position = get_camera_ref()->position;
   AllegroFlare::vec2d delta = target_position - current_camera_position;
   AllegroFlare::vec2d largest_possible_fabs_delta = AllegroFlare::Vec2D(room_width*0.5, room_height*0.5);

   get_camera_ref()->position += (delta * 0.1);

   float distance = AllegroFlare::distance(get_camera_ref()->position, target_position);

   AllegroFlare::vec2d abs_delta = AllegroFlare::Vec2D(distance * 0.01, distance * 0.01);
   float xtra_zoom = (abs_delta.x + abs_delta.y);
   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / (4.8 + xtra_zoom), 1.0 / (4.5 + xtra_zoom));

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


