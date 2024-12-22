

#include <AllegroFlare/Prototypes/MeshFPS/Screen.hpp>

#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Physics/CollisionMeshCollisionStepper.hpp>
#include <AllegroFlare/PlayerInputControllers/Generic.hpp>
#include <AllegroFlare/RouteEventDatas/ActivateScreenByIdentifier.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <tuple>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MeshFPS
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::GameConfigurations::Base* game_configuration, std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* entities, AllegroFlare::Physics::CollisionMesh* collision_mesh)
   : AllegroFlare::Screens::Gameplay()
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , game_configuration(game_configuration)
   , hud_camera({})
   , live_camera({})
   , entities(entities)
   , collision_mesh(collision_mesh)
   , visual_mesh(nullptr)
   , gems_collected(0)
   , collision_observer({})
   , on_finished_callback_func()
   , on_finished_callback_func_user_data(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_model_bin]: error: guard \"get_initialized()\" not met.");
   this->model_bin = model_bin;
}


void Screen::set_game_configuration(AllegroFlare::GameConfigurations::Base* game_configuration)
{
   this->game_configuration = game_configuration;
}


void Screen::set_hud_camera(AllegroFlare::Camera2D hud_camera)
{
   this->hud_camera = hud_camera;
}


void Screen::set_live_camera(AllegroFlare::Camera3D live_camera)
{
   this->live_camera = live_camera;
}


void Screen::set_entities(std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* entities)
{
   this->entities = entities;
}


void Screen::set_collision_mesh(AllegroFlare::Physics::CollisionMesh* collision_mesh)
{
   this->collision_mesh = collision_mesh;
}


void Screen::set_visual_mesh(AllegroFlare::Model3D* visual_mesh)
{
   this->visual_mesh = visual_mesh;
}


void Screen::set_gems_collected(int gems_collected)
{
   this->gems_collected = gems_collected;
}


void Screen::set_on_finished_callback_func(std::function<void(AllegroFlare::Prototypes::MeshFPS::Screen*, void*)> on_finished_callback_func)
{
   this->on_finished_callback_func = on_finished_callback_func;
}


void Screen::set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data)
{
   this->on_finished_callback_func_user_data = on_finished_callback_func_user_data;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::GameConfigurations::Base* Screen::get_game_configuration() const
{
   return game_configuration;
}


AllegroFlare::Camera2D Screen::get_hud_camera() const
{
   return hud_camera;
}


AllegroFlare::Camera3D Screen::get_live_camera() const
{
   return live_camera;
}


std::vector<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>* Screen::get_entities() const
{
   return entities;
}


AllegroFlare::Physics::CollisionMesh* Screen::get_collision_mesh() const
{
   return collision_mesh;
}


AllegroFlare::Model3D* Screen::get_visual_mesh() const
{
   return visual_mesh;
}


int Screen::get_gems_collected() const
{
   return gems_collected;
}


std::function<void(AllegroFlare::Prototypes::MeshFPS::Screen*, void*)> Screen::get_on_finished_callback_func() const
{
   return on_finished_callback_func;
}


void* Screen::get_on_finished_callback_func_user_data() const
{
   return on_finished_callback_func_user_data;
}


bool Screen::get_initialized() const
{
   return initialized;
}


void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::initialize]: error: guard \"model_bin\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);

   live_camera.stepout = AllegroFlare::Vec3D(0, 1.25, 0); // FPS camera
   live_camera.tilt = 0.0;
   live_camera.near_plane = 0.1;
   live_camera.far_plane = 500.0;

   //live_camera.stepout = AllegroFlare::Vec3D(0, 0.25, 10); // Third person
   //live_camera.tilt = 0.8;

   // Create a player input controller for the 0th entity
   create_and_set_player_input_controller_for_0th_entity();

   initialized = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

AllegroFlare::Prototypes::MeshFPS::Entities::Base* Screen::find_0th_entity()
{
   if (!(entities))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::find_0th_entity]: error: guard \"entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::find_0th_entity]: error: guard \"entities\" not met");
   }
   if (!((entities->size() > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::find_0th_entity]: error: guard \"(entities->size() > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::find_0th_entity]: error: guard \"(entities->size() > 0)\" not met");
   }
   return entities->at(0);
}

void Screen::create_and_set_player_input_controller_for_0th_entity()
{
   AllegroFlare::PlayerInputControllers::Generic *result_player_input_controller =
      new AllegroFlare::PlayerInputControllers::Generic();

   result_player_input_controller->set_on_time_step_update([this](AllegroFlare::Vec2D control_movement, double, double){
      //find_0th_entity()->get_velocity_ref().position.x = pos.x * 0.1;
      //find_0th_entity()->get_velocity_ref().position.z = pos.y * 0.1;
      //bool moving_forward = false;
      //bool moving_backward = false;
      //bool moving_right = false;
      //bool moving_left = false;

      //control_movement = pos;
      //if (moving_forward) control_movement.y = -1;
      //if (moving_backward) control_movement.y = 1;
      //if (moving_right) control_movement.x = 1;
      //if (moving_left) control_movement.x = -1;

      auto entity = find_0th_entity();

      // Relative to camera:
      float angle = live_camera.spin;
      float x_prime = control_movement.x * std::cos(angle) - control_movement.y * std::sin(angle);
      float y_prime = control_movement.x * std::sin(angle) + control_movement.y * std::cos(angle);
      entity->get_velocity_ref().position.x = x_prime * 0.1;
      entity->get_velocity_ref().position.z = y_prime * 0.1;
   });

   set_player_input_controller(result_player_input_controller);
}

void Screen::update()
{
   float step_duration = 1.0f;

   //
   // Apply environmental forces (gravity, air drag)
   //

   float gravity = AllegroFlare::Physics::CollisionMeshCollisionStepper::DEFAULT_GRAVITY;
   float air_drag = AllegroFlare::Physics::CollisionMeshCollisionStepper::DEFAULT_AIR_DRAG;
   AllegroFlare::Vec3D velocity_direction = AllegroFlare::Vec3D(0.0f, 1.0f, 0.0f).normalized();

   for (auto &entity : *entities)
   {
      if (!entity->active || !entity->affected_by_environmental_forces) continue;

      entity->get_velocity_ref().position += velocity_direction * gravity * step_duration;
      entity->get_velocity_ref().position *= (1.0 - air_drag);
   }


   //
   // Step entities
   //

   // Build the entities list to be stepped by the stepper
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>
      collision_stepper_entities;
   collision_stepper_entities.reserve(entities->size());
   for (auto &entity : *entities)
   {
      if (!entity->active || !entity->collides_with_environment) continue;

      collision_stepper_entities.push_back(std::make_tuple(
         &entity->get_placement_ref().position,
         &entity->get_velocity_ref().position,
         (void*)entity
      ));
   }

   if (collision_stepper_entities.empty()) throw std::runtime_error("asdfasdf");

   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set_collision_mesh(collision_mesh);
   stepper.set__entities(&collision_stepper_entities);
   stepper.disable_applying_environmental_forces();
   stepper.step(step_duration);


   //
   // Observe change in entity<->entity collisions
   //

   std::set<void*> collidables;
   auto player_entity = find_0th_entity();
   for (auto &entity : *entities)
   {
      if (entity == player_entity) continue;
      if (!entity->active || !entity->collides_with_player) continue;
      collidables.insert(entity);
   }
   collision_observer.set_subject(find_0th_entity());
   collision_observer.set_collidables(collidables);
   collision_observer.set_on_test_collide([](void* subject, void* collidable) -> bool {
      return static_cast<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>(subject)->
         collides(static_cast<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>(collidable));
   });
   collision_observer.process();

   // Process "entered" collisions
   for (auto &entered : collision_observer.get_entered())
   {
      // TODO: Consider extracting this to a method
      AllegroFlare::Prototypes::MeshFPS::Entities::Base* entity =
         static_cast<AllegroFlare::Prototypes::MeshFPS::Entities::Base*>(entered);
      entity->active = false;
      entity->visible = false;

      gems_collected++;
   }


   //
   // Update the position of the camera
   //

   live_camera.position = find_0th_entity()->get_placement_ref().position;

   return;
}

void Screen::render()
{
   ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
   live_camera.setup_projection_on(target_bitmap);

   // Draw the visual mesh
   if (visual_mesh)
   {
      visual_mesh->draw();
   }

   // TODO: Draw the entities (models?, bounding boxes?)
   al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
   auto player_entity = find_0th_entity();
   for (auto &entity : *entities)
   {
      if (!entity->active || !entity->visible) continue;
      //if (entity == player_entity) continue;

      std::vector<ALLEGRO_VERTEX> box_line_vertices = entity->build_line_list_vertices();
      std::vector<ALLEGRO_VERTEX> box_triangle_vertices = entity->build_triangle_list_vertices_for_faces();
      al_draw_prim(&box_line_vertices[0], nullptr, nullptr, 0, box_line_vertices.size(), ALLEGRO_PRIM_LINE_LIST);
      al_draw_prim(&box_triangle_vertices[0], nullptr, nullptr, 0, box_triangle_vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   }
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);

   // NOTE: For now, don't clear so that update() (with the legacy classes) has an opportunity to render debug
   // visuals
   al_set_render_state(ALLEGRO_DEPTH_TEST, 0);
   if (collision_mesh)
   {
      // TODO: Consider using additive mesh
      collision_mesh->draw(ALLEGRO_COLOR{0.2, 0.2, 0.3, 0.3});
   }
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);


   hud_camera.setup_dimensional_projection(target_bitmap);
   al_draw_textf(
      obtain_hud_font(),
      ALLEGRO_COLOR{1, 0.65, 0, 1.0},
      40,
      30,
      ALLEGRO_ALIGN_LEFT,
      "GEMS: %d",
      gems_collected
   );


   //ALLEGRO_COLOR col=AllegroFlare::color::azure);
   return;
}

void Screen::call_on_finished_callback_func()
{
   // TODO: Test this callback call
   if (on_finished_callback_func) on_finished_callback_func(this, on_finished_callback_func_user_data);
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::game_event_func]: error: guard \"game_event\" not met");
   }
   // game_configuration->handle_game_event(game_event);
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::primary_update_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::primary_update_func(time_now, delta_time);
   // Update stuff here (take into account delta_time)
   update();
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   // Render stuff here
   render();
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::key_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::key_down_func]: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::Screens::Gameplay::key_down_func(ev);

   //bool keyboard_control_caught = false;
   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_W: {
         //toggle_drawing_debug_info();
      } break;

      case ALLEGRO_KEY_A: {
         //toggle_minimap_visibility();
      } break;

      case ALLEGRO_KEY_S: {
         //toggle_minimap_visibility();
      } break;

      case ALLEGRO_KEY_D: {
         //toggle_minimap_visibility();
      } break;

      case ALLEGRO_KEY_J: {
         live_camera.spin -= ALLEGRO_PI * 0.25;
      } break;

      case ALLEGRO_KEY_K: {
         live_camera.spin += ALLEGRO_PI * 0.25;
      } break;

      //case ALLEGRO_KEY_W:
      //case ALLEGRO_KEY_UP: {
         //player_up_pressed = true;
      //} break;

      //case ALLEGRO_KEY_A:
      //case ALLEGRO_KEY_LEFT: {
         //player_left_pressed = true;
      //} break;

      //case ALLEGRO_KEY_S:
      //case ALLEGRO_KEY_DOWN: {
         //player_down_pressed = true;
      //} break;

      //case ALLEGRO_KEY_D:
      //case ALLEGRO_KEY_RIGHT: {
         //player_right_pressed = true;
      //} break;

      //case ALLEGRO_KEY_C: {
         //set_player_controlled_entity(find_primary_camera());
      //} break;

      //case ALLEGRO_KEY_Q: {
         //keyboard_control_caught = true;
         //set_player_controlled_entity(find_primary_camera());
      //} break;

      //case ALLEGRO_KEY_SPACE:
      //case ALLEGRO_KEY_E:
      //case ALLEGRO_KEY_I: {
         //if (infer_player_controlled_entity_is_camera())
         //{
            //interact_with_focused_object(); // TODO: Find a way to move this to the controller
            //keyboard_control_caught = true;
         //}
      //} break;

      case ALLEGRO_KEY_ESCAPE: {
         // NOTE: For production, you will want to emit the EVENT_PAUSE_GAME. This will crash during test because
         // there is no router. Externally, the body for on_paused_callback might be:
         //event_emitter->emit_router_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME);
         
         // NOTE: For testing, previously the call_on_finished_callback_func was called:
         // call_on_finished_callback_func();

         call_on_paused_callback_func();
         //keyboard_control_caught = true;
      } break;

      default: {
         // Nothing here
      } break;
   }


   //if (player_input_controller_exists())
   //{
      // TODO: Consider that keyboard_control_caught might need to be taken into account
      //get_player_input_controller()->key_down_func(ev);
   //}


   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::key_up_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::key_up_func]: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::Screens::Gameplay::key_up_func(ev);

   // This method is DEBUGGING
   switch(ev->keyboard.keycode)
   {
      //case ALLEGRO_KEY_UP:
      //case ALLEGRO_KEY_W: {
         //player_up_pressed = false;
      //} break;

      //case ALLEGRO_KEY_LEFT:
      //case ALLEGRO_KEY_A: {
         //player_left_pressed = false;
      //} break;

      //case ALLEGRO_KEY_DOWN:
      //case ALLEGRO_KEY_S: {
         //player_down_pressed = false;
      //} break;

      //case ALLEGRO_KEY_RIGHT:
      //case ALLEGRO_KEY_D: {
         //player_right_pressed = false;
      //} break;

      default: {
         // Nothing here
      } break;
   }

   //if (player_input_controller_exists())
   //{
      // TODO: Consider that keyboard_control_caught might need to be taken into account
      //get_player_input_controller()->key_up_func(ev);
   //}

   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::virtual_control_button_up_func(
      player, virtual_controller, virtual_controller_button_num, is_repeat
   );
   // TODO: this function
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::virtual_control_button_down_func(
      player, virtual_controller, virtual_controller_button_num, is_repeat
   );
   // TODO: this function
   //call_on_finished_callback_func(); // Consider technique to exit
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MeshFPS::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* Screen::obtain_hud_font()
{
   return font_bin->auto_get("Oswald-Medium.ttf -52");
}


} // namespace MeshFPS
} // namespace Prototypes
} // namespace AllegroFlare


