#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithInteractionFixture.hpp>
#include <AllegroFlare/Physics/CollisionMeshCollisionStepper.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <allegro5/allegro_color.h> // for al_color_name();
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Rulers.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Useful.hpp> // For draw_crosshair


static void draw_3d_line(AllegroFlare::vec3d start, AllegroFlare::vec3d end, ALLEGRO_COLOR col=AllegroFlare::color::red)
{
   ALLEGRO_VERTEX vtx[2];
   vtx[0] = AllegroFlare::build_vertex(start.x, start.y, start.z, col, 0, 0);
   vtx[1] = AllegroFlare::build_vertex(end.x, end.y, end.z, col, 0, 0);
   al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
}


class TestEntity
{
public:
   AllegroFlare::Vec3D position;
   AllegroFlare::Vec3D velocity;
   void draw(bool focused=false)
   {
      draw_crosshair(position, focused ? AllegroFlare::color::yellow : AllegroFlare::color::aquamarine, focused?2:1);
      draw_3d_line(position, position + velocity, AllegroFlare::color::pink);
   }
};


class AllegroFlare_Physics_CollisionMeshCollisionStepperTest : public ::testing::Test {};
class AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture
   : public AllegroFlare::Testing::WithInteractionFixture
{
public:
   AllegroFlare::Vec3D entity_spawn_position;
   AllegroFlare::ModelBin model_bin;
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   AllegroFlare::Physics::CollisionMesh *collision_mesh;
   AllegroFlare::Camera2D hud_camera;
   AllegroFlare::Camera3D live_camera;
   float air_drag;
   float gravity;
   int focused_entity_index;

   AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture()
      : entity_spawn_position(0, 0.001, 0)
      , model_bin()
      , entities()
      , collision_mesh(nullptr)
      , hud_camera()
      , live_camera()
      , air_drag(AllegroFlare::Physics::CollisionMeshCollisionStepper::DEFAULT_AIR_DRAG)
      , gravity(AllegroFlare::Physics::CollisionMeshCollisionStepper::DEFAULT_GRAVITY)
      , focused_entity_index(0)
   {
      model_bin.set_full_path(get_data_path() + "models/");
   }

   void setup_map(std::string map_model_identifier="collision_mesh_with_various_terrain_forms-05.obj")
   {
      if (collision_mesh) throw std::runtime_error("ya8g9du0afus0fa");

      collision_mesh = new AllegroFlare::Physics::CollisionMesh;
      collision_mesh->load(model_bin[map_model_identifier]);
      //collision_mesh->load();
   }

   void run_interactive_simulation()
   {
      if (!collision_mesh) throw std::runtime_error("nixopfbjnxiodpf");

      AllegroFlare::Camera3D target_camera;
      if (false)
      { // First person
         target_camera.stepout = AllegroFlare::Vec3D(0, 1.75, 0);
         target_camera.tilt = 0.0;
      }
      if (false)
      { // Third person
         target_camera.stepout = AllegroFlare::Vec3D(0, 1.75, 8);
         target_camera.tilt = 0.3;
      }
      if (false)
      { // Top down
         target_camera.stepout = AllegroFlare::Vec3D(0, 0, 10);
         target_camera.tilt = 0.98;
      }
      if (true)
      { // Gobal birds eye
         target_camera.stepout = AllegroFlare::Vec3D(0, 0, 20);
         target_camera.tilt = 0.98;
      }

      live_camera = target_camera;

      // Add an entity
      TestEntity *entity = new TestEntity;
      entity->position = entity_spawn_position;
      entities.push_back(std::make_tuple(&entity->position, &entity->velocity, (void*)entity));

      // Moving
      bool moving_forward = false;
      bool moving_backward = false;
      bool moving_right = false;
      bool moving_left = false;

      AllegroFlare::Vec2D control_movement;
      ALLEGRO_FONT *font = get_any_font();

      while(interactive_test_wait_for_event())
      {
         ALLEGRO_EVENT &current_event = *interactive_test_get_current_event();

         switch(current_event.type)
         {
            case ALLEGRO_EVENT_TIMER:
            {
               // Update the camera position
               blend(&live_camera, &target_camera);

               // Ensure the entity has some velocity
               if (false)
               {
                  if (moving_forward) entity->velocity.z = -0.1;
                  if (moving_backward) entity->velocity.z = 0.1;
                  if (moving_right) entity->velocity.x = 0.1;
                  if (moving_left) entity->velocity.x = -0.1;
               }

               if (true)
               { // control movement based on camera view perspective
                  control_movement = { 0, 0 };
                  if (moving_forward) control_movement.y = -1;
                  if (moving_backward) control_movement.y = 1;
                  if (moving_right) control_movement.x = 1;
                  if (moving_left) control_movement.x = -1;

                  // Relative to camera:
                  float angle = live_camera.spin;
                  float x_prime = control_movement.x * std::cos(angle) - control_movement.y * std::sin(angle);
                  float y_prime = control_movement.x * std::sin(angle) + control_movement.y * std::cos(angle);
                  entity->velocity.x = x_prime * 0.1;
                  entity->velocity.z = y_prime * 0.1;
               }

               // Create and use a stepper
               AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
               stepper.set_air_drag(air_drag);
               stepper.set_gravity(gravity);
               stepper.set__entities(&entities);
               stepper.set_collision_mesh(collision_mesh);
               //stepper.set_redirect_strategy(
                  //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_REFLECT_SURFACE
               //);
               stepper.step();

               // Prevent entity from falling eternally to the ground
               if (entity->position.y < -5)
               {
                  //entity->position = { 0, 0, 0 };
                  entity->position = { 4, 0, 2 };
                  entity->velocity = { 0, 0, 0 };
               }

               // Update the camera position
               //blend(&live_camera, &target_camera);
               //live_camera.blend(&target_camera, 0.2);
               //camera.position.x += 0.01;
               //camera.position.z -= 0.035;
               //camera.tilt += 0.0002; 
               //camera.spin -= 0.002; 

               // Have the camera track the position of the entity
               live_camera.position = entity->position;

               // Setup the rendering
               ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
               live_camera.setup_projection_on(target_bitmap);
               clear();

               // Draw the collision mesh
               if (collision_mesh) collision_mesh->draw(ALLEGRO_COLOR{0.2, 0.2, 0.3, 0.3});

               // Draw entities
               int i=0;
               for (auto &entity_info : entities)
               {
                  //entity->draw();
                  static_cast<TestEntity*>(std::get<2>(entity_info))->draw(i==focused_entity_index);
                  i++;
               }

               // TODO: Restore default projection for the HUD here
               hud_camera.setup_dimensional_projection(al_get_target_bitmap());
               al_draw_multiline_textf(
                  font,
                  ALLEGRO_COLOR{1, 1, 1, 1},
                  30,
                  20,
                  1920-30*2,
                  al_get_font_line_height(font),
                  ALLEGRO_ALIGN_LEFT,
                  "position\n"
                  "   x: %f\n" 
                  "   y: %f\n" 
                  "   z: %f\n"
                  ,
                  entity->position.x,
                  entity->position.y,
                  entity->position.z
               );

               auto focused_entity = entities[focused_entity_index];
               al_draw_multiline_textf(
                  font,
                  ALLEGRO_COLOR{1, 1, 1, 1},
                  30,
                  20+200,
                  1920-30*2,
                  al_get_font_line_height(font),
                  ALLEGRO_ALIGN_LEFT,
                  "world\n"
                  "   entities: %d\n" 
                  "   faces: %d\n" 
                  "\n"
                  "\n"
                  "stepper\n"
                  "   entities: %d\n" 
                  "   num_collision_steps: %d\n" 
                  "\n"
                  "\n"
                  "focused_entity\n"
                  "   index: %d\n" 
                  "   position:\n"
                  "      x: %f\n" 
                  "      y: %f\n" 
                  "      z: %f\n"
                  "   velocity:\n"
                  "      x: %f\n" 
                  "      y: %f\n" 
                  "      z: %f\n"
                  ,
                  entities.size(),
                  collision_mesh->get_num_faces(),
                  stepper.num_collision_step_infos(),
                  stepper.get_num_collision_steps(),
                  focused_entity_index,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->position.x,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->position.y,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->position.z,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->velocity.x,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->velocity.y,
                  static_cast<TestEntity*>(std::get<2>(focused_entity))->velocity.z
               );

               interactive_test_render_status();
               al_flip_display();
            }
            break;

            //// For example:
            //case ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT:
            //{
               //std::cout << "[AllegroFlare_Elements_MultiListTestWithAllegroRenderingFixture]: INFO: "
                         //<< "Play sound effect event was emitted. "
                         //<< std::endl;
            //}
            //break;

            case ALLEGRO_EVENT_KEY_UP:
            {
               //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
               switch(current_event.keyboard.keycode)
               {
                  case ALLEGRO_KEY_W:
                     moving_forward = false;
                  break;

                  case ALLEGRO_KEY_S:
                     moving_backward = false;
                  break;

                  case ALLEGRO_KEY_D:
                     moving_right = false;
                  break;

                  case ALLEGRO_KEY_A:
                     moving_left = false;
                  break;
               }
            } break;

            case ALLEGRO_EVENT_KEY_CHAR:
            {
               bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
               switch(current_event.keyboard.keycode)
               {
                  case ALLEGRO_KEY_ENTER:
                     // Do something
                  break;

                  case ALLEGRO_KEY_TAB:
                     if (shift)
                     {
                        focused_entity_index--;
                        if (focused_entity_index < 0) focused_entity_index = entities.size()-1;
                     }
                     else
                     {
                        focused_entity_index++;
                        if (focused_entity_index >= entities.size()) focused_entity_index = 0;;
                     }
                  break;
               }
            } break;

            case ALLEGRO_EVENT_KEY_DOWN:
            {
               //bool shift = current_event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
               switch(current_event.keyboard.keycode)
               {
                  case ALLEGRO_KEY_ENTER:
                     // Do something
                  break;

                  case ALLEGRO_KEY_W:
                     moving_backward = false;
                     moving_forward = true;
                  break;

                  case ALLEGRO_KEY_S:
                     moving_backward = true;
                     moving_forward = false;
                  break;

                  case ALLEGRO_KEY_D:
                     moving_left = false;
                     moving_right = true;
                  break;

                  case ALLEGRO_KEY_A:
                     moving_left = true;
                     moving_right = false;
                  break;

                  case ALLEGRO_KEY_RIGHT:
                     target_camera.spin += 0.25 * ALLEGRO_PI;
                  break;

                  case ALLEGRO_KEY_LEFT:
                     target_camera.spin -= 0.25 * ALLEGRO_PI;
                  break;
               }
            } break;
         }
      }
   }

   void blend(AllegroFlare::Camera3D* source_, AllegroFlare::Camera3D* target_)
   {
      AllegroFlare::Camera3D &source = *source_;
      AllegroFlare::Camera3D &target = *target_;
      float mul = 0.1;
      
      //source.position = (source.position - target.position) * mul + source.position;
      source.position = (target.position - source.position) * mul + source.position;
      source.spin = (target.spin - source.spin) * mul + source.spin;
      source.tilt = (target.tilt - source.tilt) * mul + source.tilt;
      source.stepout = (target.stepout - source.stepout) * mul + source.stepout;
      source.zoom = (target.zoom - source.zoom) * mul + source.zoom;
      source.near_plane = (target.near_plane - source.near_plane) * mul + source.near_plane;
      source.far_plane = (target.far_plane - source.far_plane) * mul + source.far_plane;
   }
};



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Physics::CollisionMeshCollisionStepper collision_mesh3dcollision_stepper;
}


/*
In the year of 2016
A labyrinth of immense size was built

It was never finished

The labyrinth brought a promise
It was meant as a great gift to the gods
*/


void draw_plane_line(float x, float y, float length, float normal_x, float normal_y, ALLEGRO_COLOR color)
{
   // Normalize the normal vector
   float magnitude = std::sqrt(normal_x * normal_x + normal_y * normal_y);
   if (magnitude != 0)
   {
      normal_x /= magnitude;
      normal_y /= magnitude;
   }

   // Calculate a direction vector perpendicular to the normal
   float direction_x = -normal_y;
   float direction_y = normal_x;

   // Calculate the start and end points of the line
   float start_x = x - direction_x * length / 2.0f;
   float start_y = y - direction_y * length / 2.0f;
   float end_x = x + direction_x * length / 2.0f;
   float end_y = y + direction_y * length / 2.0f;

   // Draw the line representing the plane
   al_draw_line(start_x, start_y, end_x, end_y, color, 2.0f);
}


void draw_point_and_vector(
      AllegroFlare::Vec3D position,
      AllegroFlare::Vec3D velocity,
      ALLEGRO_COLOR color=ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3}
   )
{
   al_draw_circle(position.x, position.y, 10.0, color, 1.0);

   // velocity line
   al_draw_line(
      position.x,
      position.y,
      position.x+velocity.x,
      position.y+velocity.y,
      color,
      //ALLEGRO_COLOR{0.3, 0.3, 0.3, 0.3},
      //ALLEGRO_COLOR{1.0, 0.8, 0.5, 1.0},
      2.0
   );
}



void create_response_diagram(
   ALLEGRO_FONT *font = nullptr,
   AllegroFlare::Vec3D position = { -200, 0, 0 },
   AllegroFlare::Vec3D velocity = { 400, 0, 0 },
   float face_collision_stepout = 50.0f,
   AllegroFlare::Vec3D face_normal = AllegroFlare::Vec3D(-1, -0.01, 0).normalized(),
   float time_to_collision = 0.5,
   AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy =
      AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
   AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy =
      AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE
)
{
   AllegroFlare::Placement2D subject_placement;
   subject_placement.position = { 1920/2, 1080/2 };


   //clear();
   subject_placement.start_transform();


   //AllegroFlare::Vec3D position = { -200, 0, 0 }; // A velocity just left of the wall
   //AllegroFlare::Vec3D velocity = { 400, 0, 0 }; // A velocity moving right
   //float face_collision_stepout = 50.0f;
   //AllegroFlare::Vec3D face_normal = AllegroFlare::Vec3D(-1, 0, 0).normalized(); // A wall facing left
   //AllegroFlare::Vec3D face_normal = AllegroFlare::Vec3D(-1, -1, 0).normalized(); // A wall angled up 45degrees
   //AllegroFlare::Vec3D face_normal = AllegroFlare::Vec3D(-1, -0.5, 0).normalized(); // A wall tilted back
   //AllegroFlare::Vec3D face_normal = AllegroFlare::Vec3D(-1, -0.01, 0).normalized(); // A wall tilted back
   //float time_to_collision = 0.5;

   // Capture the before state
   AllegroFlare::Vec3D position_before = position;
   AllegroFlare::Vec3D velocity_before = velocity;
   AllegroFlare::Vec3D point_of_intersection = position + time_to_collision * velocity;

   AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision(
      &position,
      &velocity,
      time_to_collision,
      &face_normal,
      face_collision_stepout,
      stepout_strategy,
      redirect_strategy
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_DIRECTLY_UP,
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::STEPOUT_REFLECT_SURFACE
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::STEPOUT_EXTRUDE_FACE_NORMAL
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_DIRECTLY_UP
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_STOP_VERTICAL
      //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE
   );

   AllegroFlare::Vec3D position_after = position;
   AllegroFlare::Vec3D velocity_after = velocity;

   //EXPECT_EQ(-0.001f, position.x);

   //
   // Render the outcome
   //

   //clear();
   //subject_placement.start_transform();

   // Draw the wall
   //al_draw_line(0, -200, 0, 200, ALLEGRO_COLOR{0.6, 0.2, 0.4, 1.0}, 2.0);
   draw_plane_line(0, 0, 600, face_normal.x, face_normal.y, ALLEGRO_COLOR{0.6, 0.2, 0.4, 1.0});

   // Draw the point of intersection
   AllegroFlare::Rulers::draw_crosshair_blue(point_of_intersection.x, point_of_intersection.y);

   // Draw the before position and velocity
   draw_point_and_vector(position_before, velocity_before, al_color_name("blue"));
   draw_point_and_vector(position_after, velocity_after, al_color_name("orange"));

   // Restore the transform
   subject_placement.restore_transform();

   // Draw the debug info
   al_draw_multiline_textf(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      30,
      20,
      1920-30*2,
      al_get_font_line_height(font),
      ALLEGRO_ALIGN_LEFT,
      "position (before)\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      "position (after)\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      "velocity (before)\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      "velocity (after)\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      "face normal\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      "reaction configuration\n"
      "   face_collision_stepout: %f\n"
      "   stepout_strategy: %s\n"
      "   redirect_strategy: %s\n"
      "\n"
      "point of intersection\n"
      "   x: %f\n" 
      "   y: %f\n" 
      "   z: %f\n"
      "\n"
      ,
      position_before.x,
      position_before.y,
      position_before.z,
      position_after.x,
      position_after.y,
      position_after.z,
      velocity_before.x,
      velocity_before.y,
      velocity_before.z,
      velocity_after.x,
      velocity_after.y,
      velocity_after.z,
      face_normal.x,
      face_normal.y,
      face_normal.z,
      face_collision_stepout,
      AllegroFlare::Physics::CollisionMeshCollisionStepper::to_string(stepout_strategy).c_str(),
      AllegroFlare::Physics::CollisionMeshCollisionStepper::to_string(redirect_strategy).c_str(),
      point_of_intersection.x,
      point_of_intersection.y,
      point_of_intersection.z
   );


   al_draw_multiline_textf(
      font,
      ALLEGRO_COLOR{0.6, 0.65, 1, 1},
      1920/2,
      100,
      1920/2,
      al_get_font_line_height(font),
      ALLEGRO_ALIGN_CENTER,
      "%s\n"
      "%s\n"
      ,
      AllegroFlare::Physics::CollisionMeshCollisionStepper::to_string(stepout_strategy).c_str(),
      AllegroFlare::Physics::CollisionMeshCollisionStepper::to_string(redirect_strategy).c_str()
   );

   //subject_placement.restore_transform();

   //al_flip_display();
   //al_rest(1);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__respond_to_collision__will_produce_typical_results__diagram_1)
{
   clear();
   create_response_diagram(
      get_any_font(),
      { -200, 0, 0 }, // position
      { 400, 0, 0 },  // velocity
      50.0,           // face_collision_stepout
      AllegroFlare::Vec3D(-1, -0.01, 0).normalized(), // face_normal
      0.5,            // time_to_collision
      AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
      AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE
   );
   al_flip_display();
   al_rest(1);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__respond_to_collision__will_produce_typical_results__diagram_2)
{
   clear();
   create_response_diagram(
      get_any_font(),
      { -200, 0, 0 }, // position
      { 400, 0, 0 },  // velocity
      50.0,           // face_collision_stepout
      AllegroFlare::Vec3D(-0.5, -0.5, 0).normalized(), // face_normal
      0.5,            // time_to_collision
      AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
      AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE
   );
   al_flip_display();
   al_rest(1);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__respond_to_collision__will_produce_typical_results__diagram_3)
{
   clear();
   create_response_diagram(
      get_any_font(),
      { -200, 0, 0 }, // position
      { 400, 0, 0 },  // velocity
      50.0,           // face_collision_stepout
      AllegroFlare::Vec3D(-0.25, -0.75, 0).normalized(), // face_normal
      0.5,            // time_to_collision
      AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
      AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_REFLECT_SURFACE
   );
   al_flip_display();
   al_rest(1);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__calculate_collisions__when_no_collision_occurs__will_calculate_the_collision_step_that_\
occurs_on_a_single_entity)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models/");

   // Setup our test context
   AllegroFlare::Placement2D subject_placement;
   subject_placement.position = { 1920/2, 1080/2 };
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   AllegroFlare::Physics::CollisionMesh *collision_mesh = new AllegroFlare::Physics::CollisionMesh;
   collision_mesh->load(model_bin["box_with_angled_walls-01z.obj"]);
   //collision_mesh->load();

   // Create an entity that will be stepped
   TestEntity *test_entity = new TestEntity;
   test_entity->position = { 0, 0, 0 };
   test_entity->velocity = { 1, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity->position, &test_entity->velocity, (void*)test_entity));

   // Setup the stepper
   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set_air_drag(0.0);
   stepper.set__entities(&entities);
   stepper.set_collision_mesh(collision_mesh);

   // Calculate the collisions
   stepper.calculate_collisions();

   // Grab the stepper results
   std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> collision_step_results =
      stepper.get_collision_step_infos();

   ASSERT_EQ(1, collision_step_results.size());

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_1 = collision_step_results[0];
   EXPECT_EQ(test_entity, collision_step_result_1.entity);
   EXPECT_EQ(1.0, collision_step_result_1.time);
   EXPECT_EQ(nullptr, collision_step_result_1.colliding_face);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__calculate_collisions__when_a_collision_does_occur__will_calculate_the_collision_step_that_\
occurs_on_a_single_entity)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models/");

   // Setup our test context
   AllegroFlare::Placement2D subject_placement;
   subject_placement.position = { 1920/2, 1080/2 };
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   AllegroFlare::Physics::CollisionMesh *collision_mesh = new AllegroFlare::Physics::CollisionMesh;
   collision_mesh->load(model_bin["box_with_angled_walls-01z.obj"]);
   //collision_mesh->load();

   // Create an entity that will be stepped
   TestEntity *test_entity = new TestEntity;
   test_entity->position = { 6.95, 0, 3.0 }; // There's a wall from (7,0,2)---(7,0,5)
   test_entity->velocity = { 1.0, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity->position, &test_entity->velocity, (void*)test_entity));

   // Setup the stepper
   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set_air_drag(0.0);
   stepper.set__entities(&entities);
   stepper.set_collision_mesh(collision_mesh);

   // Calculate the collisions
   stepper.calculate_collisions();

   // Grab the stepper results
   std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> collision_step_results =
      stepper.get_collision_step_infos();

   ASSERT_EQ(1, collision_step_results.size());

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_1 = collision_step_results[0];
   EXPECT_EQ(test_entity, collision_step_result_1.entity);
   EXPECT_NEAR(0.05f, collision_step_result_1.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_1.colliding_face);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__calculate_collisions__when_a_simultanious_collision_does_occur__will_calculate_the_collision_step_that_\
occurs_on_multiple_entities)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models/");

   // Setup our test context
   AllegroFlare::Placement2D subject_placement;
   subject_placement.position = { 1920/2, 1080/2 };
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   AllegroFlare::Physics::CollisionMesh *collision_mesh = new AllegroFlare::Physics::CollisionMesh;
   collision_mesh->load(model_bin["box_with_angled_walls-01z.obj"]);
   //collision_mesh->load();

   // Create entities that will experience "simultanious" collisions
   TestEntity *test_entity1 = new TestEntity;
   test_entity1->position = { 6.95, 0, 3.0 }; // There's a wall from (7,0,2)---(7,0,5)
   test_entity1->velocity = { 1.0, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity1->position, &test_entity1->velocity, (void*)test_entity1));

   TestEntity *test_entity2 = new TestEntity;
   test_entity2->position = { 6.95, 0, 3.5 }; // There's a wall from (7,0,2)---(7,0,5)
   test_entity2->velocity = { 1.0, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity2->position, &test_entity2->velocity, (void*)test_entity2));

   TestEntity *test_entity3 = new TestEntity;
   test_entity3->position = { 6.95, 0, 4.0 }; // There's a wall from (7,0,2)---(7,0,5)
   test_entity3->velocity = { 1.0, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity3->position, &test_entity3->velocity, (void*)test_entity3));

   // Setup the stepper
   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set_air_drag(0.0);
   stepper.set__entities(&entities);
   stepper.set_collision_mesh(collision_mesh);

   // Calculate the collisions
   stepper.calculate_collisions();

   // Grab the stepper results
   std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> collision_step_results =
      stepper.get_collision_step_infos();

   ASSERT_EQ(3, collision_step_results.size());

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_1 = collision_step_results[0];
   EXPECT_EQ(test_entity1, collision_step_result_1.entity);
   EXPECT_NEAR(0.05f, collision_step_result_1.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_1.colliding_face);

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_2 = collision_step_results[1];
   EXPECT_EQ(test_entity2, collision_step_result_2.entity);
   EXPECT_NEAR(0.05f, collision_step_result_2.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_2.colliding_face);

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_3 = collision_step_results[2];
   EXPECT_EQ(test_entity3, collision_step_result_3.entity);
   EXPECT_NEAR(0.05f, collision_step_result_3.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_3.colliding_face);

   // For light sanity check, check all the entities collided on the same face
   AllegroFlare::Physics::CollisionMeshFace *face = collision_step_result_1.colliding_face;
   EXPECT_EQ(face, collision_step_result_2.colliding_face);
   EXPECT_EQ(face, collision_step_result_3.colliding_face);

   // Check all the entities collided at the same time (with 0 floating point margin for error, in this case);
   float collision_time = collision_step_result_1.time;
   EXPECT_EQ(collision_time, collision_step_result_2.time);
   EXPECT_EQ(collision_time, collision_step_result_3.time);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__calculate_collisions__when_some_simultanious_collisions_occur_but_not_all__\
will_calculate_the_collision_steps_as_expected)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models/");

   // Setup our test context
   AllegroFlare::Placement2D subject_placement;
   subject_placement.position = { 1920/2, 1080/2 };
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   AllegroFlare::Physics::CollisionMesh *collision_mesh = new AllegroFlare::Physics::CollisionMesh;
   collision_mesh->load(model_bin["box_with_angled_walls-01z.obj"]);
   //collision_mesh->load();

   // Create an entities that will be stepped
   TestEntity *test_entity1 = new TestEntity;
   test_entity1->position = { 6.95, 0, 3.0 }; // There's a wall from (7,0,2)---(7,0,5) facing left
   test_entity1->velocity = { 1.0, 0, 0 };    // Moving into the wall
   entities.push_back(std::make_tuple(&test_entity1->position, &test_entity1->velocity, (void*)test_entity1));

   TestEntity *test_entity2 = new TestEntity;
   test_entity2->position = { 1.05, 0, 3.5 }; // There's a wall from (1,0,1)---(1,0,9) facing right
   test_entity2->velocity = { -1.0, 0, 0 };    // Moving into the wall
   entities.push_back(std::make_tuple(&test_entity2->position, &test_entity2->velocity, (void*)test_entity2));

   TestEntity *test_entity3 = new TestEntity; // This entity will not collide in this step
   test_entity3->position = { 6.95, 0, 5.5 }; // There's a wall from (7,0,2)---(7,0,5) facing left, entity is below it
   test_entity3->velocity = { 1.0, 0, 0 };
   entities.push_back(std::make_tuple(&test_entity3->position, &test_entity3->velocity, (void*)test_entity3));

   // Setup the stepper
   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set_air_drag(0.0);
   stepper.set__entities(&entities);
   stepper.set_collision_mesh(collision_mesh);

   // Calculate the collisions
   stepper.calculate_collisions();

   // Grab the stepper results
   std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> collision_step_results =
      stepper.get_collision_step_infos();

   ASSERT_EQ(3, collision_step_results.size());

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_1 = collision_step_results[0];
   EXPECT_EQ(test_entity1, collision_step_result_1.entity);
   EXPECT_NEAR(0.05f, collision_step_result_1.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_1.colliding_face);

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_2 = collision_step_results[1];
   EXPECT_EQ(test_entity2, collision_step_result_2.entity);
   EXPECT_NEAR(0.05f, collision_step_result_2.time, 0.00001f);
   EXPECT_NE(nullptr, collision_step_result_2.colliding_face);

   AllegroFlare::Physics::CollisionMeshCollisionStepInfo &collision_step_result_3 = collision_step_results[2];
   EXPECT_EQ(test_entity3, collision_step_result_3.entity);
   EXPECT_EQ(1.0f, collision_step_result_3.time);
   EXPECT_EQ(nullptr, collision_step_result_3.colliding_face);

   // For light sanity check, check that the simultanious collisions are occurring on differnet faces (in the
   // context of this specific test)
   EXPECT_NE(collision_step_result_1.colliding_face, collision_step_result_2.colliding_face);

   // Check all the entities collided at the same time (with 0 floating point margin for error, in this case);
   float collision_time = collision_step_result_1.time;
   EXPECT_NEAR(collision_time, collision_step_result_2.time, 0.00001f);
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithAllegroRenderingFixture,
   CAPTURE__step__will_not_blow_up)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_data_path() + "models/");

   // Load the collision mesh
   AllegroFlare::Physics::CollisionMesh *collision_mesh = new AllegroFlare::Physics::CollisionMesh;
   collision_mesh->load(model_bin["magick_world-04.obj"]);
   //collision_mesh->load();

   // Build a camera
   AllegroFlare::Camera3D camera;
   camera.stepout = AllegroFlare::Vec3D(0, 1.75, 8);
   camera.tilt = 0.3; 

   // Build a set of entities (adding a single entity)
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> entities;
   TestEntity *entity = new TestEntity;
   entities.push_back(std::make_tuple(&entity->position, &entity->velocity, (void*)entity));

   int steps = 120;
   for (int i=0; i<steps; i++)
   {
      // Ensure the entity has some velocity (for the purpose of this test)
      entity->velocity.z = -0.2;

      // Create and use a stepper
      AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
      stepper.set__entities(&entities);
      stepper.set_collision_mesh(collision_mesh);
      stepper.step(1.0);

      // Update the camera position
      //camera.position.x += 0.01;
      //camera.position.z -= 0.035;
      camera.tilt += 0.0002; 
      camera.spin -= 0.002; 

      // Have the camera track the position of the entity
      camera.position = entity->position;

      // Setup the rendering
      ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
      camera.setup_projection_on(target_bitmap);
      clear();

      // Draw the collision mesh
      if (collision_mesh)
      {
         collision_mesh->draw(ALLEGRO_COLOR{0.2, 0.2, 0.3, 0.3});
      }

      // Draw entities
      for (auto &entity_info : entities)
      {
         static_cast<TestEntity*>(std::get<2>(entity_info))->draw();
      }

      al_flip_display();
   }
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected_with_a_few_entities)
{
   //many_terrains-01.obj
   //setup_map("some_level-02d.obj");
   setup_map("box_with_angled_walls-01z.obj");
   entity_spawn_position = AllegroFlare::Vec3D(5, 0.001, 4);

   // Set the air drag to 0 for easier collision stepping
   air_drag = 0.0f;

   // Add some entities
   TestEntity *test_entity_1 = new TestEntity;
   test_entity_1->position = AllegroFlare::Vec3D(3.0, 0, 3.0);
   test_entity_1->velocity = AllegroFlare::Vec3D(0.05, 0, 0);
   TestEntity *test_entity_2 = new TestEntity;
   test_entity_2->position = AllegroFlare::Vec3D(3.0, 0, 3.5);
   test_entity_2->velocity = AllegroFlare::Vec3D(0.05, 0, 0);
   TestEntity *test_entity_3 = new TestEntity;
   test_entity_3->position = AllegroFlare::Vec3D(3.0, 0, 4.0);
   test_entity_3->velocity = AllegroFlare::Vec3D(0.05, 0, 0);

   entities.push_back(std::make_tuple(&test_entity_1->position, &test_entity_1->velocity, (void*)test_entity_1));
   entities.push_back(std::make_tuple(&test_entity_2->position, &test_entity_2->velocity, (void*)test_entity_2));
   entities.push_back(std::make_tuple(&test_entity_3->position, &test_entity_3->velocity, (void*)test_entity_3));


   //setup_map("many_terrains-03.obj");
   //setup_map("many_terrains-01.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04-joined.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-05.obj");
   run_interactive_simulation();
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected_with_many_entities__along_floor)
{
   setup_map("box_with_angled_walls-01z.obj");
   entity_spawn_position = AllegroFlare::Vec3D(5, 0.001, 4);

   // Set the air drag to 0 for easier collision stepping
   air_drag = 0.0f;

   // Add some entities
   //int num_entities = 320;
   int num_entities = 160;
   AllegroFlare::Random random(138291);
   for (int i=0; i<num_entities; i++)
   {
      TestEntity *test_entity = new TestEntity;
      test_entity->position = AllegroFlare::Vec3D(5.0, 0.0, 5.0);
      test_entity->velocity = AllegroFlare::Vec3D(
         random.get_random_float(-0.02, 0.02), 0, random.get_random_float(-0.01, 0.01)
      );
      //test_entity->position = AllegroFlare::Vec3D(random.get_random_float(1.1, 8.9), 0, random.get_random_float(1.1, 8.9));
      //test_entity->velocity = AllegroFlare::Vec3D(
         //random.get_random_float(-0.02, 0.02), 0, random.get_random_float(-0.01, 0.01)
      //);

      entities.push_back(std::make_tuple(&test_entity->position, &test_entity->velocity, (void*)test_entity));
   }

   run_interactive_simulation();
}


TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected_with_many_entities__in_3d_with_no_gravity)
{
   setup_map("closed_box_with_angled_walls-01.obj");
   entity_spawn_position = AllegroFlare::Vec3D(5, 0.001, 4);

   // Set the air drag to 0 for easier collision stepping
   air_drag = 0.0f;
   gravity = 0.0f;

   // Add some entities
   //int num_entities = 320;
   float velocity_max = 0.02f;
   //float velocity_max = 1.0f;
   int num_entities = 160;
   //AllegroFlare::Random random(138291); // No apparent breakouts
   AllegroFlare::Random random(18291);
   for (int i=0; i<num_entities; i++)
   {
      TestEntity *test_entity = new TestEntity;
      test_entity->position = AllegroFlare::Vec3D(5.0, 2.0, 5.0);
      test_entity->velocity = AllegroFlare::Vec3D(
         random.get_random_float(-velocity_max, velocity_max), 
         random.get_random_float(-velocity_max, velocity_max), 
         random.get_random_float(-velocity_max, velocity_max)
      );
      //test_entity->position = AllegroFlare::Vec3D(random.get_random_float(1.1, 8.9), 0, random.get_random_float(1.1, 8.9));
      //test_entity->velocity = AllegroFlare::Vec3D(
         //random.get_random_float(-0.02, 0.02), 0, random.get_random_float(-0.01, 0.01)
      //);

      entities.push_back(std::make_tuple(&test_entity->position, &test_entity->velocity, (void*)test_entity));
   }

   run_interactive_simulation();
}


TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected_with_many_entities__in_3d_with_no_gravity_and_high_velocity)
{
   setup_map("closed_box_with_angled_walls-01.obj");
   entity_spawn_position = AllegroFlare::Vec3D(5, 0.001, 4);

   // Set the air drag to 0 for easier collision stepping
   air_drag = 0.0f;
   gravity = 0.0f;

   // Add some entities
   int num_entities = 320;
   //float velocity_max = 0.02f;
   float velocity_max = 1.0f;
   //int num_entities = 160;
   //AllegroFlare::Random random(138291); // No apparent breakouts
   AllegroFlare::Random random(18291);
   for (int i=0; i<num_entities; i++)
   {
      TestEntity *test_entity = new TestEntity;
      test_entity->position = AllegroFlare::Vec3D(5.0, 2.0, 5.0);
      test_entity->velocity = AllegroFlare::Vec3D(
         random.get_random_float(-velocity_max, velocity_max), 
         random.get_random_float(-velocity_max, velocity_max), 
         random.get_random_float(-velocity_max, velocity_max)
      );
      //test_entity->position = AllegroFlare::Vec3D(random.get_random_float(1.1, 8.9), 0, random.get_random_float(1.1, 8.9));
      //test_entity->velocity = AllegroFlare::Vec3D(
         //random.get_random_float(-0.02, 0.02), 0, random.get_random_float(-0.01, 0.01)
      //);

      entities.push_back(std::make_tuple(&test_entity->position, &test_entity->velocity, (void*)test_entity));
   }

   run_interactive_simulation();
}



TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected)
{
   //many_terrains-01.obj
   //setup_map("some_level-02d.obj");
   setup_map("some_level-03-bumps.obj");
   //setup_map("many_terrains-03.obj");
   //setup_map("many_terrains-01.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04-joined.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-05.obj");
   run_interactive_simulation();
}



/*
TEST_F(AllegroFlare_Physics_CollisionMeshCollisionStepperTestWithInteractionFixture,
   INTERACTIVE__CAPTURE__will_work_as_expected)
{
   //many_terrains-01.obj
   setup_map("many_terrains-01-triangulated.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-04-joined.obj");
   //setup_map("collision_mesh_with_various_terrain_forms-05.obj");
   //run_interactive_simulation();

   // Add an entity
   TestEntity *entity = new TestEntity; //(nullptr);
   entities.push_back(std::make_tuple(&entity->position, &entity->velocity, (void*)entity));
   //entities.push_back(entity);

   entity->position = { 1.99929738, -0.00000201423245, -5.96841955 };
   //entity->position = { 1.95, 0.0002, -5.96841955 };
   //entity->position = { 1.95, -0.00000201423245, -5.96841955 };
   //entity->velocity = { 0.0940000042, -0.0150400009, -0.0940000042 };
   entity->velocity = { 0.0940000042, 0.0, -0.0};


   // Create and use a stepper
   AllegroFlare::Physics::CollisionMeshCollisionStepper stepper;
   stepper.set__entities(&entities);
   stepper.set_collision_mesh(collision_mesh);

   // Step
   double step_duration = 0.963275551;
   stepper.step(step_duration);

   EXPECT_LT(entity->position.x, 2.0);
}
*/


