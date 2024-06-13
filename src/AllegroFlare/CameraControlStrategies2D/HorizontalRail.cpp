

#include <AllegroFlare/CameraControlStrategies2D/HorizontalRail.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace CameraControlStrategies2D
{


HorizontalRail::HorizontalRail()
   : AllegroFlare::CameraControlStrategies2D::Base(AllegroFlare::CameraControlStrategies2D::HorizontalRail::TYPE)
   , entity_to_follow(nullptr)
   , tracking_target_position_x(0.0)
   , tracking_target_position_y(0.0)
{
}


HorizontalRail::~HorizontalRail()
{
}


void HorizontalRail::set_entity_to_follow(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* HorizontalRail::get_entity_to_follow() const
{
   return entity_to_follow;
}


void HorizontalRail::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::HorizontalRail::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::HorizontalRail::initialize]: error: guard \"(!get_initialized())\" not met");
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::HorizontalRail::initialize]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::HorizontalRail::initialize]: error: guard \"get_camera()\" not met");
   }
   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;
   float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   get_camera_ref()->scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   get_camera_ref()->position = {room_width/2, room_height/2};

   Base::initialize();
   return;
}

void HorizontalRail::update()
{
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::CameraControlStrategies2D::HorizontalRail::update]: error: guard \"get_camera()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::CameraControlStrategies2D::HorizontalRail::update]: error: guard \"get_camera()\" not met");
   }
   //camera->position = {width/2, height/2};
   if (entity_to_follow)
   {
      tracking_target_position_x = entity_to_follow->get_place_ref().position.x;
      tracking_target_position_y = entity_to_follow->get_place_ref().position.y;
   }

   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;
   float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   // note that Shovel Knight has 4.5x4.5 sized pixels (actually 4.8 x 4.5)
      // this means:
      //     - a virtual resolution of 400x240
      //     = a native display resolution of 1920x1080 (HD)
      //     - 25 tiles x 15 tiles to fill the virtual resolution
      //     - 16x16 pixel tiles
      // see https://www.yachtclubgames.com/blog/breaking-the-nes

   //camera.scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   int room_x = (tracking_target_position_x / room_width);
   int room_y = (tracking_target_position_y / room_height);
   get_camera_ref()->position = {room_width/2, room_height/2};
   get_camera_ref()->position += AllegroFlare::vec2d(room_x * room_width, room_y * room_height);

   get_camera_ref()->position.x = tracking_target_position_x;

   return;
}


} // namespace CameraControlStrategies2D
} // namespace AllegroFlare


