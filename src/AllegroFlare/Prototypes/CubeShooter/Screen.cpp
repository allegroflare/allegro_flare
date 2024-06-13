

#include <AllegroFlare/Prototypes/CubeShooter/Screen.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/EntityFactory.hpp>
#include <AllegroFlare/Useful.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Prototypes::CubeShooter::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , model_bin(model_bin)
   , scene_root()
   , entity_factory()
   , player_controlled_entity(nullptr)
   , player_movement_control()
   , camera()
   , shader()
   , multiply_shader()
   , fog_shader()
   , depth_darken_shader()
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Screen::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::set_sample_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::set_sample_bin]: error: guard \"(!initialized)\" not met");
   }
   this->sample_bin = sample_bin;
}

void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::set_model_bin]: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"sample_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"sample_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::initialize]: error: guard \"model_bin\" not met");
   }
   entity_factory.set_scene_root(&scene_root);
   entity_factory.set_bitmap_bin(bitmap_bin);
   entity_factory.set_model_bin(model_bin);
   entity_factory.initialize();

   player_movement_control.set_thruster_max_velocity(1.0);

   //depth_darken_shader.initialize();
   multiply_shader.initialize();
   //fog_shader.initialize();
   shader = &multiply_shader;

   initialized = true;
   return;
}

void Screen::load_level()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::load_level]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::load_level]: error: guard \"initialized\" not met");
   }
   player_controlled_entity = entity_factory.add_player_ship(0, 1, 0);
   entity_factory.add_world_mesh();
   entity_factory.add_cube(4, 5, -10);
   entity_factory.add_cube(0, 1, -10);
   entity_factory.add_cube(-5, 3, -10);
   player_movement_control.set_player_controlled_entity(player_controlled_entity);
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   // for now:
   load_level();
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::update()
{
   float time_now = al_get_time();

   // update expired entities and remove entities that can be deleted
   for (auto &entity : scene_root.get_flat_list_of_descendants<AllegroFlare::Prototypes::CubeShooter::Entity>())
   {
      if (entity->has_attribute("lifespan"))
      {
         if (entity->infer_age(time_now) > entity->get_as_float("lifespan"))
         {
            entity->set("can_be_deleted");
         }
      }
   }

   // clear all entities that are flagged to be deleted
   for (auto &entity : scene_root.get_flat_list_of_descendants<AllegroFlare::Prototypes::CubeShooter::Entity>())
   {
      if (entity->has_attribute("can_be_deleted"))
      {
         // NOTE: I think this this the way to do this
         entity->reassign_parent(nullptr);
         delete entity;
      }
   }

   // update velocities based on movement controls
   player_movement_control.update(time_now);
   bool blaster_fired = player_movement_control.get_blaster_fired_on_last_update();

   // create new bullets
   if (blaster_fired)
   {
      AllegroFlare::Vec3D player_position = player_controlled_entity->get_placement_ref().position;
      entity_factory.add_player_bullet(player_position.x, player_position.y, player_position.z);
   }

   // update physics
   float air_drag = 0.05;
   float forward_air_drag = 0.02;
   // move entities by velocity
   for (auto &entity : scene_root.get_flat_list_of_descendants<AllegroFlare::Prototypes::CubeShooter::Entity>())
   {
      entity->get_placement_ref().position += entity->get_velocity_ref().position;
      entity->get_placement_ref().rotation += entity->get_velocity_ref().rotation;
      if (!entity->has_attribute("ignore_environmental_physics"))
      {
         entity->get_velocity_ref().position.x *= (1.0 - air_drag);
         entity->get_velocity_ref().position.y *= (1.0 - air_drag);
         entity->get_velocity_ref().position.z *= (1.0 - forward_air_drag);
      }
   }

   // TODO: check for collisions here (may want to revise this technique)
   std::vector<AllegroFlare::Prototypes::CubeShooter::Entity*> bullets = {};
   std::vector<AllegroFlare::Prototypes::CubeShooter::Entity*> entities_that_can_be_hit_by_bullets = {};
   for (auto &entity : scene_root.get_flat_list_of_descendants<AllegroFlare::Prototypes::CubeShooter::Entity>())
   {
      if (entity == player_controlled_entity) continue;

      if (entity->has_attribute("player_bullet")) bullets.push_back(entity);
      else if (!entity->has_attribute("ignore")) entities_that_can_be_hit_by_bullets.push_back(entity);
   }
   for (auto &bullet : bullets)
   {
      for (auto &entity_that_can_be_hit_by_bullet : entities_that_can_be_hit_by_bullets)
      {
         if (collides(bullet, entity_that_can_be_hit_by_bullet))
         {
            // TODO: play sound effect
            bullet->set_attribute("can_be_deleted");
            entity_that_can_be_hit_by_bullet->get_placement_ref().scale *= 0.5;
            if (entity_that_can_be_hit_by_bullet->get_placement_ref().scale.x < 0.24)
            {
               entity_that_can_be_hit_by_bullet->set_attribute("can_be_deleted");
            }
         }
      }
   }

   // update camera tracking camera
   camera.position.x = player_controlled_entity->get_placement_ref().position.x * 0.6;
   camera.position.y = player_controlled_entity->get_placement_ref().position.y * 0.25;
   camera.position.z = player_controlled_entity->get_placement_ref().position.z;
   float target_camera_tilt = 0.3 + camera.position.y * -0.04;
   //float roll_increment = 0.001f;
   float target_camera_spin = camera.position.x * 0.025;
   // HERE:
   float max_roll = 0.17; // 0.07 is dramatic (maybe roll control can be tied to remaining health)
                          // -0.17 feels like the gound is falling out
   float target_camera_roll = player_movement_control.get_moving_right()
                            ? max_roll
                            : (player_movement_control.get_moving_left() ? -max_roll : 0.0f);
   float spin_tilt_lag = 0.06; //1.0; //0.03;
   //player_controlled_entity->get_placement_ref().rotation.z = -target_camera_roll;

   camera.stepout = AllegroFlare::Vec3D(0, 0.3, 10);
   //camera.tilt = 0.3;
   camera.tilt= (target_camera_tilt - camera.tilt) * spin_tilt_lag + camera.tilt;
   camera.zoom = 1.1;
   // NOTE: spin+ rotates the scene as if turning your head right and strafing left
   camera.spin = (target_camera_spin - camera.spin) * spin_tilt_lag + camera.spin;
   camera.roll = (target_camera_roll - camera.roll) * 0.02 + camera.roll;

   float &player_roll = player_controlled_entity->get_placement_ref().rotation.z;
   player_roll = ((-target_camera_roll) - player_roll) * 0.03 + player_roll;

   return;
}

bool Screen::collides(AllegroFlare::Prototypes::CubeShooter::Entity* entity_a, AllegroFlare::Prototypes::CubeShooter::Entity* entity_b)
{
   AllegroFlare::Vec3D &entity_a_position = entity_a->get_placement_ref().position;
   AllegroFlare::Vec3D &entity_b_position = entity_b->get_placement_ref().position;

   AllegroFlare::Vec3D a_min = entity_a->get_min_bounding_box_coordinates() + entity_a_position;
   AllegroFlare::Vec3D a_max = entity_a->get_max_bounding_box_coordinates() + entity_a_position;
   AllegroFlare::Vec3D b_min = entity_b->get_min_bounding_box_coordinates() + entity_b_position;
   AllegroFlare::Vec3D b_max = entity_b->get_max_bounding_box_coordinates() + entity_b_position;

   return (
      a_min.x <= b_max.x &&
      a_max.x >= b_min.x &&
      a_min.y <= b_max.y &&
      a_max.y >= b_min.y &&
      a_min.z <= b_max.z &&
      a_max.z >= b_min.z
   );
}

void Screen::render_crosshair(AllegroFlare::Vec3D position)
{
   draw_crosshair(position, ALLEGRO_COLOR{1, 0, 1, 1}, 0.01);
   return;
}

void Screen::render()
{
   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_clear_depth_buffer(1);
   al_clear_to_color(ALLEGRO_COLOR{0, 0.12, 0.3, 1.0});

   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());

   camera.setup_projection_on(backbuffer);
   al_set_target_bitmap(backbuffer);

   if (shader)
   {
      multiply_shader.set_time_now(al_get_time());
      shader->activate();
   }

   for (auto &entity : scene_root.get_flat_list_of_descendants<AllegroFlare::Prototypes::CubeShooter::Entity>())
   {
      entity->get_placement_ref().start_transform();
      entity->get_model_3d_ref()->draw();
      entity->get_placement_ref().restore_transform();

      //draw_crosshair(entity->get_min_bounding_box_coordinates() + entity->get_placement_ref().position);
      //draw_crosshair(entity->get_max_bounding_box_coordinates() + entity->get_placement_ref().position);
   }
   //glCullFace(GL_BACK);  // requiring opengl should evnetually be fazed out
   //glDisable(GL_CULL_FACE);

   if (shader) shader->deactivate();

   al_restore_state(&previous_target_bitmap_state);
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::primary_timer_func]: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::key_down_func]: error: guard \"event\" not met");
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         player_movement_control.set_moving_up(true);
      break;

      case ALLEGRO_KEY_DOWN:
         player_movement_control.set_moving_down(true);
      break;

      case ALLEGRO_KEY_LEFT:
         player_movement_control.set_moving_left(true);
      break;

      case ALLEGRO_KEY_RIGHT:
         player_movement_control.set_moving_right(true);
      break;

      case ALLEGRO_KEY_X:
      case ALLEGRO_KEY_Z:
         player_movement_control.set_thruster_active(true);
      break;

      case ALLEGRO_KEY_SPACE:
         player_movement_control.set_firing_blaster(true);
      break;

      case ALLEGRO_KEY_P:
         multiply_shader.set_pulse_created_at(al_get_time());
      break;
   }
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"event\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Screen::key_up_func]: error: guard \"event_emitter\" not met");
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         player_movement_control.set_moving_up(false);
      break;

      case ALLEGRO_KEY_DOWN:
         player_movement_control.set_moving_down(false);
      break;

      case ALLEGRO_KEY_LEFT:
         player_movement_control.set_moving_left(false);
      break;

      case ALLEGRO_KEY_RIGHT:
         player_movement_control.set_moving_right(false);
      break;

      case ALLEGRO_KEY_X:
      case ALLEGRO_KEY_Z:
         player_movement_control.set_thruster_active(false);
      break;

      case ALLEGRO_KEY_SPACE:
         player_movement_control.set_firing_blaster(false);
      break;
   }
   return;
}


} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


