
#include <WickedDemos/PlayerControlControlStrategy.hpp>
#include <WickedDemos/FunzDemo.hpp>



#include <AllegroFlare/Useful.hpp>
using AllegroFlare::TAU;



PlayerControlControlStrategy::PlayerControlControlStrategy(FunzDemo *funz_demo)
   : ControlStrategyBase("PlayerControlControlStrategy")
   , funz_demo(funz_demo)
{}


void PlayerControlControlStrategy::on_activate() {
   funz_demo->camera_spinning = false;
   funz_demo->cursor_over_entity_id = -1;
}


void PlayerControlControlStrategy::on_deactivate() {
   //funz_demo->camera_spinning = true;
}


void PlayerControlControlStrategy::key_up_func(ALLEGRO_EVENT *ev)
{
   if (!funz_demo) throw std::runtime_error("[PlayerControlControlStrategy::key_up_func] error: funz_demo cannot be nullptr");
   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;

   switch(ev->keyboard.keycode)
   {
   case ALLEGRO_KEY_W:
      funz_demo->player_control.forward_backward_velocity = 0.0f;
      break;
   case ALLEGRO_KEY_A:
      funz_demo->player_control.strafe_left_right_velocity = 0.0f;
      break;
   case ALLEGRO_KEY_S:
      funz_demo->player_control.forward_backward_velocity = 0.0f;
      break;
   case ALLEGRO_KEY_D:
      funz_demo->player_control.strafe_left_right_velocity = 0.0f;
      break;
   case ALLEGRO_KEY_RIGHT:
      funz_demo->camera_spinning = false;
      funz_demo->player_control.rotation_left_right_velocity = 0.0f;
      break;
   case ALLEGRO_KEY_LEFT:
      funz_demo->camera_spinning = false;
      funz_demo->player_control.rotation_left_right_velocity = 0.0f;
      break;
   }
}


void PlayerControlControlStrategy::key_down_func(ALLEGRO_EVENT *ev)
{
   if (!funz_demo) throw std::runtime_error("[PlayerControlControlStrategy::key_down_func] error: funz_demo cannot be nullptr");
   if (!ev) throw std::runtime_error("[PlayerControlControlStrategy::key_down_func] error: ev cannot be nullptr");

   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;

   switch(ev->keyboard.keycode)
   {
   case ALLEGRO_KEY_W:
      funz_demo->player_control.forward_backward_velocity = 1.0f;
      break;
   case ALLEGRO_KEY_A:
      funz_demo->player_control.strafe_left_right_velocity = -1.0f;
      break;
   case ALLEGRO_KEY_S:
      funz_demo->player_control.forward_backward_velocity = -1.0f;
      break;
   case ALLEGRO_KEY_D:
      funz_demo->player_control.strafe_left_right_velocity = 1.0f;
      break;
   case ALLEGRO_KEY_UP:
      if (shift) funz_demo->camera_target_zoom += 0.2;
      else funz_demo->camera_target_stepout_z -= 2.0f;
      break;
   case ALLEGRO_KEY_DOWN:
      if (shift) funz_demo->camera_target_zoom -= 0.2;
      else funz_demo->camera_target_stepout_z += 2.0f;
      break;
   case ALLEGRO_KEY_RIGHT:
      funz_demo->player_control.rotation_left_right_velocity = 1.0f;
      break;
   case ALLEGRO_KEY_LEFT:
      funz_demo->player_control.rotation_left_right_velocity = -1.0f;
      break;
   }
}


void PlayerControlControlStrategy::key_char_func(ALLEGRO_EVENT *ev)
{
   if (!funz_demo) throw std::runtime_error("[PlayerControlControlStrategy::key_char_func] error: funz_demo cannot be nullptr");

   vec3d moving_right = vec3d(1, 0, 0);
   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;

   switch(ev->keyboard.keycode)
   {
   //case ALLEGRO_KEY_PAD_6:
      //funz_demo->camera_spinning = false;
      //funz_demo->camera_target_spin -= 0.2f;
      //break;
   //case ALLEGRO_KEY_PAD_4:
      //funz_demo->camera_spinning = false;
      //funz_demo->camera_target_spin += 0.2f;
      //break;
   //case ALLEGRO_KEY_PAD_2:
      //funz_demo->camera_target_stepout_z += 2.0f;
      //break;
   //case ALLEGRO_KEY_PAD_8:
      //funz_demo->camera_target_stepout_z -= 2.0f;
      //break;
   //case ALLEGRO_KEY_PAD_PLUS:
      //if (funz_demo->camera_target_zoom >= funz_demo->max_zoom) break;
      //else { funz_demo->camera_target_zoom += 0.2f; }
      //break;
   //case ALLEGRO_KEY_PAD_MINUS:
      //if (funz_demo->camera_target_zoom <= funz_demo->min_zoom) break;
      //else { funz_demo->camera_target_zoom -= 0.2f; }
      //break;
   }
}


void PlayerControlControlStrategy::primary_timer_func()
{
   if (!funz_demo) throw std::runtime_error("[PlayerControlControlStrategy::primary_timer_func] error: funz_demo cannot be nullptr");

   float velocity_strength = 0.06;
   //
   { // W - S
      float quarter_spin = TAU * 0.25f;
      float spin_to_calc = funz_demo->camera.spin - (quarter_spin);
      vec2d move_vec = vec2d(cos(spin_to_calc), sin(spin_to_calc)) * funz_demo->player_control.forward_backward_velocity * velocity_strength;
      funz_demo->camera_target_position.x += move_vec.x;
      funz_demo->camera_target_position.y += 0; // moving_right.y;
      funz_demo->camera_target_position.z += move_vec.y;
   }
   { // A - D (left-right)
      vec2d move_vec = vec2d(cos(funz_demo->camera.spin), sin(funz_demo->camera.spin)) * funz_demo->player_control.strafe_left_right_velocity * velocity_strength;
      funz_demo->camera_target_position.x += move_vec.x;
      funz_demo->camera_target_position.y += 0; // moving_right.y;
      funz_demo->camera_target_position.z += move_vec.y;
   }
   {
      funz_demo->camera_target_spin += funz_demo->player_control.rotation_left_right_velocity * velocity_strength;
   }
}



