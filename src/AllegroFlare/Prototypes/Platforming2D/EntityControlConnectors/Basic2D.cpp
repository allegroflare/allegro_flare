

#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Basic2D.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
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
   , right_pressed(0)
   , left_pressed(0)
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


void Basic2D::update_player_controls_on_player_controlled_entity()
{
   if (!(basic_2d_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::update_player_controls_on_player_controlled_entity]: error: guard \"basic_2d_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::update_player_controls_on_player_controlled_entity]: error: guard \"basic_2d_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // if this block is active, the player cannot control themselves while in the air, only when on the ground:
   //if (player_controlled_entity->exists(ADJACENT_TO_FLOOR))
   //{
      //player_controlled_entity->get_velocity_ref().position.x = 0.0;
   //}

   //if (player_controls.get_right_bumper_pressed())
   //{
      //player_controlled_entity->get_velocity_ref().position.x = 0.0;
   //}
   //else
   //{
   AllegroFlare::Vec2D player_control_velocity;

      // if this block is active, the player cannot control themselves while in the air, only when on the ground:
      if (basic_2d_entity->exists(ADJACENT_TO_FLOOR))
      {
         //player_control_velocity.x = 0.0;
         //player_controlled_entity->get_velocity_ref().position.x = 0.0;
         basic_2d_entity->get_velocity_ref().position.x = 0.0;
      }

         //if (player_controls.get_right_button_pressed())
         //{
         if (right_pressed > 0)
         {
            ////player_control_velocity.x = 1.0;
            //player_control_velocity.x = 1.0;
            //player_controlled_entity->set_bitmap_flip_h(false);
            ////player_controlled_entity->get_velocity_ref().position.x = 1.5; //2.0;
            //basic_2d_entity->get_velocity_ref().position.x = 0.0;
            player_control_velocity.x = 1.0;
         }
         //if (player_controls.get_left_button_pressed())
         //{
         if (left_pressed > 0)
         {
            player_control_velocity.x = -1.0;
            ////player_control_velocity.x = -1.0;
            //player_control_velocity.x = -1.0;
            //player_controlled_entity->set_bitmap_flip_h(true);
            ////player_controlled_entity->get_velocity_ref().position.x = -1.5; //-2.0;
         }
         //}
   //}


   float player_speed = 1.5;
   basic_2d_entity->get_velocity_ref().position.x = player_control_velocity.x * player_speed;


   return;
}

void Basic2D::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(basic_2d_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::key_down_func]: error: guard \"basic_2d_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::key_down_func]: error: guard \"basic_2d_entity\" not met");
   }
   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_LEFT:
         left_pressed++;
         //basic_2d_entity->get_velocity_ref().position.x = -1.5;
         basic_2d_entity->set_bitmap_flip_h(true);
      break;

      case ALLEGRO_KEY_RIGHT:
         right_pressed++;
         //basic_2d_entity->get_velocity_ref().position.x = 1.5;
         basic_2d_entity->set_bitmap_flip_h(false);
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
         attempt_jump();
         //set_player_controlled_entity_jump();
      break;
   }

   return;
}

void Basic2D::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(basic_2d_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::key_up_func]: error: guard \"basic_2d_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::key_up_func]: error: guard \"basic_2d_entity\" not met");
   }
   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_LEFT:
         left_pressed--;
         //basic_2d_entity->get_velocity_ref().position.x = 0.0;
      break;

      case ALLEGRO_KEY_RIGHT:
         right_pressed--;
         //basic_2d_entity->get_velocity_ref().position.x = 0.0;
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

void Basic2D::attempt_jump()
{
   if (!(basic_2d_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::attempt_jump]: error: guard \"basic_2d_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D::attempt_jump]: error: guard \"basic_2d_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // Jump if on the floor
   if (basic_2d_entity->exists(ADJACENT_TO_FLOOR))
   {
      basic_2d_entity->get_velocity_ref().position.y -= 4.25;
   }
   else if (basic_2d_entity->exists(ADJACENT_TO_LEFT_WALL)) // Wall jump
   {
      basic_2d_entity->get_velocity_ref().position.y = -3.5;
      basic_2d_entity->get_velocity_ref().position.x = 3.0;
   }
   else if (basic_2d_entity->exists(ADJACENT_TO_RIGHT_WALL))
   {
      basic_2d_entity->get_velocity_ref().position.y = -3.5;
      basic_2d_entity->get_velocity_ref().position.x = -3.0;
   }
   return;
}


} // namespace EntityControlConnectors
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


