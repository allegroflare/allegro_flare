

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
      error_message << "[SmoothSnapWithZoomEffect::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnapWithZoomEffect::initialize]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!((room_width > 0)))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_width > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!((room_height > 0)))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnapWithZoomEffect::initialize]: error: guard \"(room_height > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   // TODO: only allow setting "room_width" and "room_height" to positive values

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
      error_message << "[SmoothSnapWithZoomEffect::update]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnapWithZoomEffect::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   if (!(entity_to_follow))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnapWithZoomEffect::update]: error: guard \"entity_to_follow\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   int target_room_x = (entity_to_follow->get_place_ref().position.x / room_width);
   int target_room_y = (entity_to_follow->get_place_ref().position.y / room_height);
   AllegroFlare::vec2d target_position = {room_width/2, room_height/2};
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


