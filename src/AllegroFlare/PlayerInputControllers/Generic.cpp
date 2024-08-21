

#include <AllegroFlare/PlayerInputControllers/Generic.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace PlayerInputControllers
{


Generic::Generic()
   : AllegroFlare::PlayerInputControllers::Base(AllegroFlare::PlayerInputControllers::Generic::TYPE)
   , on_time_step_update({})
   , player_control_move_velocity({})
   , player_control_look_velocity({})
   , player_right_pressed(false)
   , player_left_pressed(false)
   , player_up_pressed(false)
   , player_down_pressed(false)
{
}


Generic::~Generic()
{
}


void Generic::set_on_time_step_update(std::function<void(AllegroFlare::Vec2D, double, double)> on_time_step_update)
{
   this->on_time_step_update = on_time_step_update;
}


std::function<void(AllegroFlare::Vec2D, double, double)> Generic::get_on_time_step_update() const
{
   return on_time_step_update;
}


void Generic::player_stop_moving()
{
   player_up_pressed = false;
   player_down_pressed = false;
   player_left_pressed = false;
   player_right_pressed = false;
   player_control_move_velocity.x = 0;
   player_control_move_velocity.y = 0;
   return;
}

void Generic::player_spin_change(float delta)
{
   //AllegroFlare::Prototypes::TileFPS::Entities::Camera3D* as_camera = camera_entity;
   //as_camera->spin += delta;
   return;
}

void Generic::player_tilt_change(float delta)
{
   //AllegroFlare::Prototypes::TileFPS::Entities::Camera3D* as_camera = camera_entity; //find_primary_camera();

   //float tilt = as_camera->tilt;

   //tilt += delta;
   //float max_tilt = 3.14 / 2;
   //if (tilt < -max_tilt) tilt = -max_tilt;
   //if (tilt > max_tilt) tilt = max_tilt;
   //as_camera->tilt = tilt;
   return;
}

AllegroFlare::Vec2D Generic::infer_player_control_move_velocity_from_keypress()
{
   AllegroFlare::Vec2D result = { 0, 0 };
   float speed = 1.0; // Running is like 0.1, walking like 0.05

   if (player_left_pressed && player_right_pressed) result.x = 0.0f;
   else if (player_left_pressed) result.x = -speed;
   else if (player_right_pressed) result.x = speed;

   if (player_up_pressed && player_down_pressed) result.y = 0.0f;
   else if (player_up_pressed) result.y = -speed;
   else if (player_down_pressed) result.y = speed;

   return result;
}

void Generic::update_time_step(double time_now, double delta_time)
{
   // NOTE: This method should likely be renamed, it's equivelent to an update on a time step. It's processed
   // along with the update in the TileFPS/Screen update method, but before physics are applied on entities
   // TODO: Update the above comment to remove TileFPS/Screen reference

   //player_control_move_velocity = infer_player_control_move_velocity_from_keypress();
   if (on_time_step_update)
   {
      player_control_move_velocity = infer_player_control_move_velocity_from_keypress();
      on_time_step_update(player_control_move_velocity, time_now, delta_time);
   }

   //kiosk_entity->move_rotor_position(player_control_move_velocity.x * 0.05);
   //float spin_multiplier = 0.05;
   //float tilt_multiplier = 0.05;
   //player_spin_change(player_control_look_velocity.x * spin_multiplier);
   //player_tilt_change(player_control_look_velocity.y * tilt_multiplier);

   //player_control_move_velocity = infer_player_control_move_velocity_from_keypress();
   //AllegroFlare::Vec3D camera_strafe_speed = calculate_strafe_xy(
         //camera_entity->spin,
         //player_control_move_velocity.x
      //);
   //AllegroFlare::Vec3D camera_forward_back_speed = calculate_forward_back_xy(
         //camera_entity->spin,
         //player_control_move_velocity.y
      //);
   //camera_entity->get_velocity_ref().position = camera_strafe_speed + camera_forward_back_speed;
   return;
}

void Generic::gameplay_suspend_func()
{
   player_stop_moving();
   // NOTE: This function is called immediately after the gameplay is suspended.
   // TODO: Consider setting states on entities, checking their state timers, etc
   return;
}

void Generic::gameplay_resume_func()
{
   player_stop_moving();
   return;
}

void Generic::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT: {
         player_left_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         player_right_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         player_up_pressed = false;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         player_down_pressed = false;
      } break;

      default: {
         // TODO: IMPORTANT: There is currently no escape from gameplay/screen
         //call_on_finished_callback_func();
      } break;
   };

   //player_stop_moving(); // TODO: Improve this movement
   return;
}

void Generic::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   // TODO: validate virtual controller type

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT: {
         player_left_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT: {
         player_right_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP: {
         player_up_pressed = true;
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN: {
         player_down_pressed = true;
      } break;

      default: {
         // TODO: IMPORTANT: There is currently no escape from gameplay/screen
         //call_on_finished_callback_func();
      } break;
   };

   return;
}

void Generic::key_down_func(ALLEGRO_EVENT* ev)
{
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_W:
      case ALLEGRO_KEY_UP: {
         player_up_pressed = true;
      } break;

      case ALLEGRO_KEY_A:
      case ALLEGRO_KEY_LEFT: {
         player_left_pressed = true;
      } break;

      case ALLEGRO_KEY_S:
      case ALLEGRO_KEY_DOWN: {
         player_down_pressed = true;
      } break;

      case ALLEGRO_KEY_D:
      case ALLEGRO_KEY_RIGHT: {
         player_right_pressed = true;
      } break;

      case ALLEGRO_KEY_SPACE:
      case ALLEGRO_KEY_E:
      case ALLEGRO_KEY_I: {
         //interact_with_focused_object();
      } break;

      case ALLEGRO_KEY_ESCAPE: {
         // NOTE: For production, you will want to emit the EVENT_PAUSE_GAME. This will crash during test because
         // there is no router. Externally, the body for on_paused_callback might be:
         //event_emitter->emit_router_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME);

         // NOTE: For testing, previously the call_on_finished_callback_func was called:
         // call_on_finished_callback_func();

         //call_on_paused_callback_func();
      } break;

      default: {
         // Nothing here
      } break;
   }

   return;
}

void Generic::key_up_func(ALLEGRO_EVENT* ev)
{
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
      case ALLEGRO_KEY_W: {
         player_up_pressed = false;
      } break;

      case ALLEGRO_KEY_LEFT:
      case ALLEGRO_KEY_A: {
         player_left_pressed = false;
      } break;

      case ALLEGRO_KEY_DOWN:
      case ALLEGRO_KEY_S: {
         player_down_pressed = false;
      } break;

      case ALLEGRO_KEY_RIGHT:
      case ALLEGRO_KEY_D: {
         player_right_pressed = false;
      } break;

      default: {
         // Nothing here
      } break;
   }

   return;
}

void Generic::joy_axis_func(ALLEGRO_EVENT* ev)
{
   float axis_min_movement_threshold = 0.1f; // 0.05 is not enough for red joystick
   //float spin_multiplier = 0.01;
   //float tilt_multiplier = 0.01;
   // The "look" stick
   switch(ev->joystick.stick)
   {
      case 0: { // The "look" stick (spin, along the x axis)
         //float spin_delta = 0.0f;
         switch(ev->joystick.axis)
         {
            case 2:
               if (std::fabs(ev->joystick.pos) < axis_min_movement_threshold)
               {
                  player_control_look_velocity.x = 0.0f;
               }
               else
               {
                  player_control_look_velocity.x = ev->joystick.pos;
               }
            break;
         }
         //player_control_look_velocity.x = spin_delta;
         //player_spin_change(spin_delta * spin_multiplier);
      } break;
      case 1: { // The "look" stick (tilt, along the y axis)
         //float tilt_delta = 0.0f;
         switch(ev->joystick.axis)
         {
            case 0:
               if (std::fabs(ev->joystick.pos) < axis_min_movement_threshold)
               {
                  player_control_look_velocity.y = 0.0f;
               }
               else
               {
                  player_control_look_velocity.y = ev->joystick.pos;
               }
            break;
         }
         //player_control_look_velocity.y = tilt_delta;
         //player_tilt_change(tilt_delta * tilt_multiplier);
      } break;
   }

   switch(ev->joystick.stick)
   {
      case 0: { // The "move" stick
         switch(ev->joystick.axis)
         {
            case 0:
               if (ev->joystick.pos > 0.2)
               {
                  player_right_pressed = true;
                  player_left_pressed = false;
               }
               else if (ev->joystick.pos < -0.2)
               {
                  player_left_pressed = true;
                  player_right_pressed = false;
               }
               else
               {
                  player_left_pressed = false;
                  player_right_pressed = false;
               }
            break;
            case 1:
               if (ev->joystick.pos > 0.2)
               {
                  player_down_pressed = true;
                  player_up_pressed = false;
               }
               else if (ev->joystick.pos < -0.2)
               {
                  player_up_pressed = true;
                  player_down_pressed = false;
               }
               else
               {
                  player_up_pressed = false;
                  player_down_pressed = false;
               }
            break;
         }
      } break;
   }

   return;
}

void Generic::mouse_down_func(ALLEGRO_EVENT* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PlayerInputControllers::Generic::mouse_down_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PlayerInputControllers::Generic::mouse_down_func]: error: guard \"ev\" not met");
   }
   switch(ev->mouse.button)
   {
      //case 1: {
         //interact_with_focused_object();
      //} break;
   }
   return;
}

void Generic::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   // TODO: Validate spin change
   ///*
   float spin_delta = ev->mouse.dx;
   float tilt_delta = ev->mouse.dy;
   float spin_multiplier = 0.001;
   float tilt_multiplier = 0.001;
   player_spin_change(spin_delta * spin_multiplier);
   player_tilt_change(tilt_delta * tilt_multiplier);


   // HACK
   /*
   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   int current_display_flags = al_get_display_flags(current_display);
   bool this_display_is_fullscreen = current_display_flags & ALLEGRO_FULLSCREEN_WINDOW;
   bool this_display_is_windowed = !this_display_is_fullscreen;

   //if (this_display_is_fullscreen)
   //{
      //throw std::runtime_error("this_display_is_fullscreen");
   //}
   //else
   //{
      //throw std::runtime_error("this_display_is_not_fullscreen");
   //}


   //ALLEGRO_FULLSCREEN_WINDOW

   // TODO: Look into what/why this HACK_sysname is needed
   bool this_system_is_a_mac = (HACK_sysname == "Darwin");

   if (this_display_is_windowed && this_system_is_a_mac)
   {
      if (current_display)
      {
         al_set_mouse_xy(
            current_display,
            al_get_display_width(current_display)*0.5,
            al_get_display_height(current_display)*0.5
         );
      }
   }

   if (!this_display_is_windowed && !this_system_is_a_mac)
   {
      // Warp on windows in fullscreen
      if (current_display)
      {
         al_set_mouse_xy(
            current_display,
            al_get_display_width(current_display)*0.5,
            al_get_display_height(current_display)*0.5
         );
      }
   }
   */


   //float x_delta = ev->mouse->dx;
   //result->tilt = 0.13;            // look up(-)/down(+)
   //result->spin = 0.2;             // set a good start initial spin
   // TODO: this function
   return;
}

AllegroFlare::Vec3D Generic::calculate_strafe_xy(float spin, float displacement)
{
   type: AllegroFlare::Vec3D result;
   AllegroFlare::Vec2D move_vec(std::cos(spin), std::sin(spin));
   result.x = move_vec.x * displacement;
   result.y = 0;
   result.z = move_vec.y * displacement;
   return result;
}

AllegroFlare::Vec3D Generic::calculate_forward_back_xy(float spin, float displacement)
{
   type: AllegroFlare::Vec3D result;
   AllegroFlare::Vec2D move_vec(-std::sin(spin), std::cos(spin));
   result.x = move_vec.x * displacement;
   result.y = 0;
   result.z = move_vec.y * displacement;
   return result;
}


} // namespace PlayerInputControllers
} // namespace AllegroFlare


