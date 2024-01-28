

#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Basic2D.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace EntityControlConnectors
{


Basic2D::Basic2D(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* basic_2d_entity)
   : AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base(AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::TYPE)
   , basic_2d_entity(basic_2d_entity)
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_basic_2d_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* basic_2d_entity)
{
   this->basic_2d_entity = basic_2d_entity;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2D::get_basic_2d_entity() const
{
   return basic_2d_entity;
}


void Basic2D::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(basic_2d_entity))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::key_down_func]: error: guard \"basic_2d_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::key_down_func: error: guard \"basic_2d_entity\" not met");
   }
   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_LEFT:
         //player_control_velocity.x = 0.0;
         //player_controls.set_left_button_pressed(true);
      break;

      case ALLEGRO_KEY_RIGHT:
         //player_control_velocity.x = 1.0;
         //player_controls.set_right_button_pressed(true);
      break;

      case ALLEGRO_KEY_UP:
         //player_control_velocity.y = -1.0;
         //player_controls.set_up_button_pressed(true);
         //check_player_collisions_with_doors();
      break;

      case ALLEGRO_KEY_DOWN:
         //player_control_velocity.y = 1.0;
      break;

      case ALLEGRO_KEY_SPACE:
         //set_player_controlled_entity_jump();
      break;
   }

   return;
}


} // namespace EntityControlConnectors
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


