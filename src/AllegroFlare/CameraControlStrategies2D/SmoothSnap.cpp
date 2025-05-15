

#include <AllegroFlare/CameraControlStrategies2D/SmoothSnap.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CameraControlStrategies2D
{


SmoothSnap::SmoothSnap(float room_width, float room_height)
   : AllegroFlare::CameraControlStrategies2D::Base(AllegroFlare::CameraControlStrategies2D::SmoothSnap::TYPE)
   , room_width(room_width)
   , room_height(room_height)
   , entity_to_follow(nullptr)
   , tracking_target_position_x(0.0)
   , tracking_target_position_y(0.0)
{
}


SmoothSnap::~SmoothSnap()
{
}


void SmoothSnap::set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* SmoothSnap::get_entity_to_follow() const
{
   return entity_to_follow;
}


void SmoothSnap::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnap::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnap::initialize]: error: guard \"(!get_initialized())\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnap::initialize]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnap::initialize]: error: guard \"get_camera()\" not met");
   }
   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   get_camera_ref()->position = AllegroFlare::Vec2D{room_width/2, room_height/2};

   Base::initialize();
   return;
}

void SmoothSnap::update()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnap::update]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnap::update]: error: guard \"get_initialized()\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::SmoothSnap::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::SmoothSnap::update]: error: guard \"get_camera()\" not met");
   }
   // If the camera loses track of the "entity_to_follow" (the tracking target dies for example), this logic will
   // retain the last coordinate that had been tracked, and use it until a new tracking target is introduced.
   if (entity_to_follow)
   {
      tracking_target_position_x = entity_to_follow->get_place_ref().position.x;
      tracking_target_position_y = entity_to_follow->get_place_ref().position.y;
   }

   int room_x = (tracking_target_position_x / room_width);
   int room_y = (tracking_target_position_y / room_height);
   AllegroFlare::vec2d target = {room_width/2, room_height/2};
   target += AllegroFlare::vec2d(room_x * room_width, room_y * room_height);

   AllegroFlare::vec2d position = get_camera_ref()->position;

   AllegroFlare::vec2d delta = target - position;

   get_camera_ref()->position += (delta * 0.1);

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


