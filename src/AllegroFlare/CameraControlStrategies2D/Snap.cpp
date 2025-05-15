

#include <AllegroFlare/CameraControlStrategies2D/Snap.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CameraControlStrategies2D
{


Snap::Snap()
   : AllegroFlare::CameraControlStrategies2D::Base(AllegroFlare::CameraControlStrategies2D::Snap::TYPE)
   , entity_to_follow(nullptr)
{
}


Snap::~Snap()
{
}


void Snap::set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Snap::get_entity_to_follow() const
{
   return entity_to_follow;
}


void Snap::update()
{
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::Snap::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::Snap::update]: error: guard \"get_camera()\" not met");
   }
   if (!(entity_to_follow))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::Snap::update]: error: guard \"entity_to_follow\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::Snap::update]: error: guard \"entity_to_follow\" not met");
   }
   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;

   float room_width = assumed_tile_width * 25;
   float room_height = assumed_tile_height * 15;

   int room_x = (entity_to_follow->get_place_ref().position.x / room_width);
   int room_y = (entity_to_follow->get_place_ref().position.y / room_height);
   get_camera_ref()->position = AllegroFlare::Vec2D{room_width/2, room_height/2};
   get_camera_ref()->position += AllegroFlare::vec2d(room_x * room_width, room_y * room_height);

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


