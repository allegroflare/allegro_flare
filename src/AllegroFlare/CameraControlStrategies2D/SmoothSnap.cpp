

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
      error_message << "[SmoothSnap::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SmoothSnap::initialize: error: guard \"(!get_initialized())\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnap::initialize]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SmoothSnap::initialize: error: guard \"get_camera()\" not met");
   }
   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   get_camera_ref()->position = {room_width/2, room_height/2};

   Base::initialize();
   return;
}

void SmoothSnap::update()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnap::update]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SmoothSnap::update: error: guard \"get_initialized()\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnap::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SmoothSnap::update: error: guard \"get_camera()\" not met");
   }
   if (!(entity_to_follow))
   {
      std::stringstream error_message;
      error_message << "[SmoothSnap::update]: error: guard \"entity_to_follow\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SmoothSnap::update: error: guard \"entity_to_follow\" not met");
   }
   int room_x = (entity_to_follow->get_place_ref().position.x / room_width);
   int room_y = (entity_to_follow->get_place_ref().position.y / room_height);
   AllegroFlare::vec2d target = {room_width/2, room_height/2};
   target += AllegroFlare::vec2d(room_x * room_width, room_y * room_height);

   AllegroFlare::vec2d position = get_camera_ref()->position;

   AllegroFlare::vec2d delta = target - position;

   get_camera_ref()->position += (delta * 0.1);

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


