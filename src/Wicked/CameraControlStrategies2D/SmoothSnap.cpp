

#include <Wicked/CameraControlStrategies2D/SmoothSnap.hpp>

#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace CameraControlStrategies2D
{


SmoothSnap::SmoothSnap(float room_width, float room_height)
   : Wicked::CameraControlStrategies2D::Base()
   , room_width(room_width)
   , room_height(room_height)
   , entity_to_follow(nullptr)
{
}


SmoothSnap::~SmoothSnap()
{
}


void SmoothSnap::set_entity_to_follow(Wicked::Entities::Basic2D* entity_to_follow)
{
   this->entity_to_follow = entity_to_follow;
}


Wicked::Entities::Basic2D* SmoothSnap::get_entity_to_follow() const
{
   return entity_to_follow;
}


void SmoothSnap::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "SmoothSnap" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "SmoothSnap" << "::" << "initialize" << ": error: " << "guard \"get_camera()\" not met";
      throw std::runtime_error(error_message.str());
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
      error_message << "SmoothSnap" << "::" << "update" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(get_camera()))
   {
      std::stringstream error_message;
      error_message << "SmoothSnap" << "::" << "update" << ": error: " << "guard \"get_camera()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(entity_to_follow))
   {
      std::stringstream error_message;
      error_message << "SmoothSnap" << "::" << "update" << ": error: " << "guard \"entity_to_follow\" not met";
      throw std::runtime_error(error_message.str());
   }
   //camera->position = {width/2, height/2};

   //float assumed_tile_width = 16.0f;
   //float assumed_tile_height = 16.0f;

   //float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   //float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   // note that Shovel Knight has 4.5x4.5 sized pixels (actually 4.8 x 4.5)
      // this means:
      //     - a virtual resolution of 400x240
      //     = a native display resolution of 1920x1080 (HD)
      //     - 25 tiles x 15 tiles to fill the virtual resolution
      //     - 16x16 pixel tiles
      // see https://www.yachtclubgames.com/blog/breaking-the-nes

   //camera.scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
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
} // namespace Wicked


