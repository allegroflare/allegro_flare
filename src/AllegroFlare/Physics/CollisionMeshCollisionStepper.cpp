

#include <AllegroFlare/Physics/CollisionMeshCollisionStepper.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/Useful3D/Ray.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Physics
{


CollisionMeshCollisionStepper::CollisionMeshCollisionStepper(AllegroFlare::Physics::CollisionMesh* collision_mesh, std::vector<AllegroFlare::Physics::CollisionMesh*> collision_meshes, std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* _entities, float face_collision_stepout)
   : collision_mesh(collision_mesh)
   , collision_meshes(collision_meshes)
   , _entities(_entities)
   , face_collision_stepout(face_collision_stepout)
   , stepout_strategy(StepoutStrategy::STEPOUT_REVERSE_VELOCITY)
   , redirect_strategy(RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE)
   , apply_environmental_forces(true)
   , air_drag(DEFAULT_AIR_DRAG)
   , gravity(DEFAULT_GRAVITY)
   , collision_step_infos({})
   , on_collision_with_face({})
   , num_collision_steps(0)
{
}


CollisionMeshCollisionStepper::~CollisionMeshCollisionStepper()
{
}


void CollisionMeshCollisionStepper::set_collision_mesh(AllegroFlare::Physics::CollisionMesh* collision_mesh)
{
   this->collision_mesh = collision_mesh;
}


void CollisionMeshCollisionStepper::set_collision_meshes(std::vector<AllegroFlare::Physics::CollisionMesh*> collision_meshes)
{
   this->collision_meshes = collision_meshes;
}


void CollisionMeshCollisionStepper::set__entities(std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* _entities)
{
   this->_entities = _entities;
}


void CollisionMeshCollisionStepper::set_face_collision_stepout(float face_collision_stepout)
{
   this->face_collision_stepout = face_collision_stepout;
}


void CollisionMeshCollisionStepper::set_stepout_strategy(AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy)
{
   this->stepout_strategy = stepout_strategy;
}


void CollisionMeshCollisionStepper::set_redirect_strategy(AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy)
{
   this->redirect_strategy = redirect_strategy;
}


void CollisionMeshCollisionStepper::set_air_drag(float air_drag)
{
   this->air_drag = air_drag;
}


void CollisionMeshCollisionStepper::set_gravity(float gravity)
{
   this->gravity = gravity;
}


void CollisionMeshCollisionStepper::set_num_collision_steps(int num_collision_steps)
{
   this->num_collision_steps = num_collision_steps;
}


AllegroFlare::Physics::CollisionMesh* CollisionMeshCollisionStepper::get_collision_mesh() const
{
   return collision_mesh;
}


std::vector<AllegroFlare::Physics::CollisionMesh*> CollisionMeshCollisionStepper::get_collision_meshes() const
{
   return collision_meshes;
}


std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* CollisionMeshCollisionStepper::get__entities() const
{
   return _entities;
}


float CollisionMeshCollisionStepper::get_face_collision_stepout() const
{
   return face_collision_stepout;
}


AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy CollisionMeshCollisionStepper::get_stepout_strategy() const
{
   return stepout_strategy;
}


AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy CollisionMeshCollisionStepper::get_redirect_strategy() const
{
   return redirect_strategy;
}


bool CollisionMeshCollisionStepper::get_apply_environmental_forces() const
{
   return apply_environmental_forces;
}


float CollisionMeshCollisionStepper::get_air_drag() const
{
   return air_drag;
}


float CollisionMeshCollisionStepper::get_gravity() const
{
   return gravity;
}


std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> CollisionMeshCollisionStepper::get_collision_step_infos() const
{
   return collision_step_infos;
}


std::function<void(AllegroFlare::Physics::CollisionMeshCollisionStepInfo*)> CollisionMeshCollisionStepper::get_on_collision_with_face() const
{
   return on_collision_with_face;
}


int CollisionMeshCollisionStepper::get_num_collision_steps() const
{
   return num_collision_steps;
}


int CollisionMeshCollisionStepper::num_collision_step_infos()
{
   return collision_step_infos.size();
}

void CollisionMeshCollisionStepper::disable_applying_environmental_forces()
{
   apply_environmental_forces = false;
   return;
}

void CollisionMeshCollisionStepper::enable_applying_environmental_forces()
{
   apply_environmental_forces = false;
   return;
}

void CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision(AllegroFlare::Vec3D* position_, AllegroFlare::Vec3D* velocity_, float time_to_collision, AllegroFlare::Vec3D* face_normal_, float face_collision_stepout, AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy, AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy)
{
   if (!(position_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"position_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"position_\" not met");
   }
   if (!(velocity_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"velocity_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"velocity_\" not met");
   }
   if (!(face_normal_))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"face_normal_\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision]: error: guard \"face_normal_\" not met");
   }
   auto &position = *position_;
   auto &velocity = *velocity_;
   auto &face_normal = *face_normal_;
   vec3d point_of_intersection = position + time_to_collision * velocity;
   vec3d final_offset_from_intersection_point = vec3d(0.0, 0.0, 0.0);

   //
   // For the special case of making floors more natural to walk along, this block might change the collision
   // response (stepout and velocity redirection) so that it better emulates walking along floor smoothly.
   // TODO: Look into cases where the STEPOUT_DIRECTLY_UP could potentially lead to a mesh breakout.
   // "breakout" is when an entity does not collide against the wall surface and instead passes through it due
   // to a buggy collision scenario.

   if (face_normal.y < 0)
   {
      // This slope is facing "down", I don't think anything special comes from this?
   }
   else
   {
      // This slope is facing "up", could be a potential flat surface to stand on.
      // TODO: Consider caching this data in the Face class.

      float abs_ascent = fabs(face_normal.y);
      if (abs_ascent > 0.85) // This number could be modified per entity to represent a gravity vector, for example
                             // around a giant ball similar to mario galaxy.
      {
         // NOTE: If reached here, the entity is on standard, stable-enough flat-enough ground to walk on.
         // Slope is "flat-ish". This is the threshold for walking over the surface at a regular horizontal
         // velocity that is not affected by the slope.
         //state_flags.set(Entity::ON_GROUND); // TODO: Sort out how and where ON_GROUND will be applied

         //final_offset_from_intersection_point = vec3d(0.0, face_collision_stepout, 0.0);
         stepout_strategy = StepoutStrategy::STEPOUT_DIRECTLY_UP;
         //state_flags.set(Entity::ON_GROUND); // TODO: Sort out how and where ON_GROUND will be applied
         redirect_strategy = RedirectStrategy::REDIRECT_STOP_VERTICAL;
      }
      else
      {
         // Treat normally, no change in how the surface reaction should occur
      }
   }


   //
   // Pick the strategy for how the entity is to be repositioned as a result of the collision
   // Entity is positioned at a distance from the collision surface to avoid tunneling through due to precision
   // errors, or otherwise.

   switch (stepout_strategy)
   {
      case AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY: {
         // TODO: Note that normalizing here if result is 0 0 0 will cause NaN NaN NaN. For now, leading up to
         // this method will check for that scenario.
         // TODO: Note that there is a concern if the face_collision_stepout moves the colliding entity
         // further back than its original position, could potentially cause a breakout if this repositioning causes
         // it to tunnel through another nearby face.
         vec3d reverse_velocity_dir = AllegroFlare::Vec3D(-velocity.x, -velocity.y, -velocity.z).normalized();
         final_offset_from_intersection_point = reverse_velocity_dir * face_collision_stepout;
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REFLECT_SURFACE: {
         // TODO: Note that normalizing here if result is 0 0 0 will cause NaN NaN NaN
         vec3d reflect_normal = reflect(velocity, face_normal).normalized();
         final_offset_from_intersection_point = reflect_normal * face_collision_stepout;
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_EXTRUDE_FACE_NORMAL: {
         final_offset_from_intersection_point = face_normal * face_collision_stepout;
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_NONE: {
         final_offset_from_intersection_point = { 0, 0, 0 };
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_DIRECTLY_UP: {
         // TODO: Test edge case scenarios under this collision stepout strategy
         final_offset_from_intersection_point = { 0, face_collision_stepout, 0 };
      } break;

      default: {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision",
            "Unhandled case for this StepoutStrategy."
         );
      } break;
   }

   // Entity is moved to the new position
   position = point_of_intersection + final_offset_from_intersection_point;


   //
   // Pick the strategy for how to handle the velocity as a result of the collision.

   switch (redirect_strategy)
   {
      case AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_REFLECT_SURFACE: {
         // TODO: Note that normalizing here if result is 0 0 0 will cause NaN NaN NaN
         vec3d reflect_normal = reflect(velocity, face_normal).normalized();
         velocity = reflect_normal * velocity.get_magnitude();
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_COMPLETE_STOP: {
         velocity = { 0, 0, 0 };
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_STOP_VERTICAL: {
         velocity.y = 0;
      } break;

      case AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE: {
         float initial_velocity_magnitude = velocity.get_magnitude();

         // TODO: Test this guard safely handles this case
         // If velocity magnitude is too low, then project() will (NaN, NaN, NaN)
         if (initial_velocity_magnitude < 0.0001)
         {
            // If the magnitude is below a threshold, simply have this stepper set the velocity to 0;
            velocity = { 0, 0, 0 };
         }
         else
         {
            vec3d projected_point = project(velocity.normalized(), AllegroFlare::Vec3D(0, 0, 0), face_normal);
            // TODO: Test this guard safely handles this case
            // If projected_point is too low, then projected_point.normalize() will (NaN, NaN, NaN)
            if (     std::fabs(projected_point.x) < 0.00001
                  && std::fabs(projected_point.y) < 0.00001
                  && std::fabs(projected_point.z) < 0.00001
               )
            {
               // If the magnitude is below a threshold, simply have this stepper set the velocity to 0;
               velocity = { 0, 0, 0 };
            }
            else
            {
               velocity = initial_velocity_magnitude * projected_point.normalized();
            }
         }
      } break;

      default: {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Physics::CollisionMeshCollisionStepper::move_to_time_of_collision_and_react_to_collision",
            "Unhandled case for this RedirectStrategy."
         );
      } break;
   }


   return;
}

float CollisionMeshCollisionStepper::calculate_collisions(float min_entity_velocity_magnitude)
{
   if (!(_entities))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::calculate_collisions]: error: guard \"_entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::calculate_collisions]: error: guard \"_entities\" not met");
   }
   if (!(collision_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::calculate_collisions]: error: guard \"collision_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::calculate_collisions]: error: guard \"collision_mesh\" not met");
   }
   // TODO: Consider scenario where an entity could collide with 2 faces in a single step, one would potentially
   // be ignored. Make sure it's the lesser collision time/step of the two.

   AllegroFlare::Physics::CollisionMesh &mesh = *collision_mesh;
   std::vector<AllegroFlare::Physics::CollisionMesh*> &meshes = collision_meshes;
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> &entities = *_entities;
   float least_collision_time = 1.0;
   float least_collision_time_for_this_entity = 1.0;
   collision_step_infos.clear();

   // Setup some data for this calculation
   AllegroFlare::Useful3D::IntersectData intersect_info;

   // Loop over each entity while processing the faces
   for (auto &entity_info : entities)
   {
      // For every entity, do step calculations
      AllegroFlare::Vec3D &position = *std::get<0>(entity_info);
      AllegroFlare::Vec3D &velocity = *std::get<1>(entity_info);
      void *entity = std::get<2>(entity_info);

      if (velocity.get_magnitude() < min_entity_velocity_magnitude) continue;

      // Add a step calculation for this entity
      // Find the least colliding time for this entity
      float least_collision_time_for_this_entity = 1.0;
      AllegroFlare::Physics::CollisionMeshFace *least_collision_time_for_this_entity_colliding_face = nullptr;

      // Setup some data for the iteration
      vec3d start_pos = position;
      vec3d end_pos = position + velocity;
      AllegroFlare::Useful3D::Ray ray(start_pos, end_pos-start_pos);


      // Create the faces processing lambda
      // This lambda technique is used here for performance reasons, in order to operate on multiple sets of faces
      // without performing a excessive embedded function calls.
      // See: https://chatgpt.com/share/6757b289-6b48-800f-af6a-d5b077bb0368
      auto process_faces = [&](auto &faces)
      {
         for (auto &face : faces)
         {
            if (face.disabled) continue;

            if (face.intersect(&ray, &intersect_info))
            {
               if (intersect_info.t >= 0.0f && intersect_info.t <= 1.0f)
               {
                  // A collision occurred on this face

                  // Capture the least collision time for this entity and the colliding face
                  if (intersect_info.t < least_collision_time_for_this_entity)
                  {
                     least_collision_time_for_this_entity = intersect_info.t;
                     least_collision_time_for_this_entity_colliding_face = &face;
                  }

                  // Capture the overall smallest collision time
                  if (intersect_info.t < least_collision_time)
                  {
                     least_collision_time = intersect_info.t;
                  }
               }
            }
         }
      };

      process_faces(mesh.get_faces_ref());
      // TODO: process indexed faces (that may be disabled)
      process_faces(mesh.get_dynamic_faces_ref());

      // TODO: Test this with multiple meshes
      for (auto &mesh : meshes)
      {
         //meshes
         process_faces(mesh->get_faces_ref());
         // TODO: process indexed faces (that may be disabled)
         process_faces(mesh->get_dynamic_faces_ref());
      }


      /*
      // Iterate all faces, see if there was a collision
      for (auto &face : mesh.get_faces_ref())
      {
         if (face.disabled) continue;

         if (face.intersect(&ray, &intersect_info))
         {
            if (intersect_info.t >= 0.0f && intersect_info.t <= 1.0f)
            {
               // A collision occurred on this face

               // Capture the least collision time for this entity and the colliding face
               if (intersect_info.t < least_collision_time_for_this_entity)
               {
                  least_collision_time_for_this_entity = intersect_info.t;
                  least_collision_time_for_this_entity_colliding_face = &face;
               }

               // Capture the overall smallest collision time
               if (intersect_info.t < least_collision_time)
               {
                  least_collision_time = intersect_info.t;
               }
            }
         }
      }
      */

      collision_step_infos.push_back(
         AllegroFlare::Physics::CollisionMeshCollisionStepInfo(
            least_collision_time_for_this_entity,
            entity,
            &position,
            &velocity,
            least_collision_time_for_this_entity_colliding_face
         )
      );

      //if (on_collision_with_surface)
   }

   return least_collision_time;
}

std::tuple<float, AllegroFlare::Physics::CollisionMeshFace*, void*> CollisionMeshCollisionStepper::find_least_collision_time_and_colliding_entity_and_face(float min_entity_velocity_magnitude)
{
   if (!(_entities))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::find_least_collision_time_and_colliding_entity_and_face]: error: guard \"_entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::find_least_collision_time_and_colliding_entity_and_face]: error: guard \"_entities\" not met");
   }
   if (!(collision_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::find_least_collision_time_and_colliding_entity_and_face]: error: guard \"collision_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::find_least_collision_time_and_colliding_entity_and_face]: error: guard \"collision_mesh\" not met");
   }
   // TODO: Consider collecting multiple entities
   // Possibly a collection ordered by float. Find the soonest, then collect ones that are also
   // slightly after (by an error margin)

   AllegroFlare::Physics::CollisionMesh &mesh = *collision_mesh;
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> &entities = *_entities;

   float least_collision_time = 1.0;
   AllegroFlare::Physics::CollisionMeshFace *colliding_face = nullptr;
   void *colliding_entity = nullptr;

   for (auto &entity_info : entities)
   {
      AllegroFlare::Vec3D &position = *std::get<0>(entity_info);
      AllegroFlare::Vec3D &velocity = *std::get<1>(entity_info);
      void *entity = std::get<2>(entity_info);

      if (velocity.get_magnitude() < min_entity_velocity_magnitude) continue;

      for (unsigned f=0; f<mesh.get_faces_ref().size(); f++)
      {
         AllegroFlare::Physics::CollisionMeshFace &face = mesh.get_faces_ref()[f];
         AllegroFlare::Useful3D::IntersectData intersect_info;
         vec3d start_pos = position;
         vec3d end_pos = position + velocity;
         AllegroFlare::Useful3D::Ray ray(start_pos, end_pos-start_pos);

         if (face.intersect(&ray, &intersect_info))
         {
            bool draw_intersection_point = true;
            if (draw_intersection_point)
            {
               vec3d collision_point = (end_pos-start_pos) * intersect_info.t + start_pos;
               draw_crosshair(collision_point, color::pink, 0.5);
            }

            if (intersect_info.t >= 0.0f && intersect_info.t <= 1.0f)
            {
               if (intersect_info.t < least_collision_time)
               {
                  least_collision_time = intersect_info.t;
                  colliding_face = &face;
                  colliding_entity = entity;
               }
            }
         }
      }
   }

   return { least_collision_time, colliding_face, colliding_entity };
}

void CollisionMeshCollisionStepper::apply_gravity_and_air_drag(float total_duration)
{
   //
   // Apply global forces (like gravity) on objects
   // NOTE: Minimum velocity *must* be greater than (GRAVITY * air_drag), other wise a still object will
   // stay suspended in space
   //

   //std::vector<Entity*> &entities = *_entities;
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> &entities = *_entities;
   //const float GRAVITY = -0.016;
   //const float AIR_DRAG = 0.06;

   for (auto &entity : entities)
   {
      //AllegroFlare::Vec3D &position = entity->position;
      //AllegroFlare::Vec3D &velocity = entity->velocity;
      //std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> &entities = *_entities;
      AllegroFlare::Vec3D &position = *std::get<0>(entity);
      AllegroFlare::Vec3D &velocity = *std::get<1>(entity);



      //float air_drag = entity->air_drag;
      //float air_drag = AIR_DRAG;

      // Clear floor flags?
      // TODO: Have this tracked so that "ON_GROUND" etc can trigger a callback
      //entities[e]->state_flags.unset(Entity::ON_GROUND);

      velocity += AllegroFlare::Vec3D(0, gravity * total_duration, 0);
      velocity = velocity * (1 - air_drag);
   }
   return;
}

void CollisionMeshCollisionStepper::step(float total_duration)
{
   if (!(_entities))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::step]: error: guard \"_entities\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::step]: error: guard \"_entities\" not met");
   }
   if (!(collision_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Physics::CollisionMeshCollisionStepper::step]: error: guard \"collision_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Physics::CollisionMeshCollisionStepper::step]: error: guard \"collision_mesh\" not met");
   }
   if (apply_environmental_forces) apply_gravity_and_air_drag(total_duration);

   //std::vector<Entity*> &entities = *_entities;
   std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>> &entities = *_entities;
   CollisionMesh &mesh = *collision_mesh;

   //
   // COLLISION TEST
   // do the sweep to find the least intersection time
   //

   float time_left_in_timestep = total_duration;
   //float time_left_in_timestep = 1.0;
   num_collision_steps = 0;

   int max_steps_to_abort = 1000;
   const float min_time_step = 1e-10f;
   //const float min_entity_velocity_magnitude = 1e-10f;
   const float min_entity_velocity_magnitude = 0.001f; //1e-f;

   while (time_left_in_timestep > min_time_step)
   {
      num_collision_steps++;
      //float least_collision_time = total_duration;
      //float duration_of_this_substep = std::min(time_left_in_timestep, least_collision_time);

      // Collision technique 1: Find the soonest intersection time
      if (false)
      {
         float least_collision_time = total_duration;
         AllegroFlare::Physics::CollisionMeshFace *colliding_face = nullptr;
         void *colliding_entity = nullptr;
         std::tie(least_collision_time, colliding_face, colliding_entity) =
            find_least_collision_time_and_colliding_entity_and_face(min_entity_velocity_magnitude);
         float duration_of_this_substep = std::min(time_left_in_timestep, least_collision_time);

         // Reposition the objects to the least intersection time
         for (auto &entity_info : entities)
         {
            // TODO: Consider the scenario where more than one object collides at this same collision time
            AllegroFlare::Vec3D &position = *std::get<0>(entity_info);
            AllegroFlare::Vec3D &velocity = *std::get<1>(entity_info);
            void *entity = std::get<2>(entity_info);

            if (velocity.get_magnitude() < min_entity_velocity_magnitude) continue;

            if (colliding_entity == entity)
            {
               // perform the actual collision response calculations on the object
               move_to_time_of_collision_and_react_to_collision(
                  &position,
                  &velocity,
                  duration_of_this_substep,
                  &colliding_face->normal,
                  face_collision_stepout
               );

               // Draw some debug info on the colliding face
               draw_3d_line(colliding_face->centroid,
                     colliding_face->centroid+colliding_face->normal*5,
                     AllegroFlare::color::black);
               //colliding_face->draw(color::orange); // If you wan to draw the colliding face
            }
            else
            {
               position += velocity * duration_of_this_substep;
            }
         }

         time_left_in_timestep -= duration_of_this_substep;
      }

      // Collision technique 2: Calculate *all* collisions, find the soonest time, move all to that time
      if (true)
      {
         //AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY;
         //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE;

         const float least_collision_time_threshold = 0.0001f;

         float least_collision_time = calculate_collisions(min_entity_velocity_magnitude);
         float duration_of_this_substep = std::min(time_left_in_timestep, least_collision_time);

         for (auto &collision_step_info : collision_step_infos)
         {
            bool entity_will_collide_at_least_time =
               (collision_step_info.time - duration_of_this_substep) <= least_collision_time_threshold;
               //fabs(collision_step_info.time - least_collision_time) <= least_collision_time_threshold;
            bool entity_does_collide_with_face = collision_step_info.colliding_face ? true : false;

            if (collision_step_info.entity_velocity->get_magnitude() < min_entity_velocity_magnitude) continue;

            if (entity_will_collide_at_least_time && entity_does_collide_with_face)
            {
               move_to_time_of_collision_and_react_to_collision(
                  collision_step_info.entity_position,
                  collision_step_info.entity_velocity,
                  collision_step_info.time, // Step to this entity's collision time so it will be aligned with
                                            // the face it collides with. Note that the collision will thus be
                                            // modified by a fraction of a time, accelerating it slightly by
                                            // by an extreemely small number, in order to reduce the margin of 
                                            // error in floating point calculations
                  //multipass_least_collision_time, // Consider if this is OK or should be the entities collision time
                  //duration_of_this_substep,
                  //&colliding_face->normal,
                  &collision_step_info.colliding_face->normal,
                  face_collision_stepout,
                  stepout_strategy,
                  redirect_strategy
                  //AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy::STEPOUT_REVERSE_VELOCITY,
                  //AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE,
               );


               if (on_collision_with_face)
               {
                  on_collision_with_face(&collision_step_info);
               }

               //if (on_collision_with_surface)
               //- name: stepout_strategy
               //  type: AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy
               //  default_argument: StepoutStrategy::STEPOUT_REVERSE_VELOCITY
               //- name: redirect_strategy
               //  type: AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy
               //  xdefault_argument: RedirectStrategy::REDIRECT_COMPLETE_STOP
               //  default_argument: RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE
            }
            else
            {
               //position += velocity * collision_step_info.time;
               *collision_step_info.entity_position +=
                  *collision_step_info.entity_velocity * duration_of_this_substep;
            }
         }

         time_left_in_timestep -= duration_of_this_substep;
         //*/
      }


      //time_left_in_timestep -= duration_of_this_substep;


      max_steps_to_abort--;
      if (max_steps_to_abort < 0)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Physics::CollisionMeshCollisionStepper::step",
            "While looping, max_steps_to_abort was exceeded."
         );
      }
   }

   return;
}

std::string CollisionMeshCollisionStepper::to_string(AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy)
{
   switch (stepout_strategy)
   {
      case StepoutStrategy::STEPOUT_UNDEF:
         return "STEPOUT_UNDEF";
      case StepoutStrategy::STEPOUT_REVERSE_VELOCITY:
         return "STEPOUT_REVERSE_VELOCITY";
      case StepoutStrategy::STEPOUT_REFLECT_SURFACE:
         return "STEPOUT_REFLECT_SURFACE";
      case StepoutStrategy::STEPOUT_EXTRUDE_FACE_NORMAL:
         return "STEPOUT_EXTRUDE_FACE_NORMAL";
      case StepoutStrategy::STEPOUT_DIRECTLY_UP:
         return "STEPOUT_DIRECTLY_UP";
      case StepoutStrategy::STEPOUT_NONE:
         return "STEPOUT_NONE";
      default:
         return "[ERROR:UNKNOWN_STEPOUT_STRATEGY]";
   }
   return "[error]";
}

std::string CollisionMeshCollisionStepper::to_string(AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy)
{
   switch (redirect_strategy)
   {
      case RedirectStrategy::REDIRECT_UNDEF:
         return "REDIRECT_UNDEF";
      case RedirectStrategy::REDIRECT_REFLECT_SURFACE:
         return "REDIRECT_REFLECT_SURFACE";
      case RedirectStrategy::REDIRECT_COMPLETE_STOP:
         return "REDIRECT_COMPLETE_STOP";
      case RedirectStrategy::REDIRECT_STOP_VERTICAL:
         return "REDIRECT_STOP_VERTICAL";
      case RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE:
         return "REDIRECT_SLIDE_ALONG_SURFACE";
      default:
         return "[ERROR:UNKNOWN_REDIRECT_STRATEGY]";
   }
   return "[error]";
}

void CollisionMeshCollisionStepper::draw_3d_line(AllegroFlare::Vec3D start, AllegroFlare::Vec3D end, ALLEGRO_COLOR col)
{
   // TODO: Consider if this can be replaced with AllegroFlare::Useful3D::draw_3d_line
   ALLEGRO_VERTEX vtx[2];
   vtx[0] = AllegroFlare::build_vertex(start.x, start.y, start.z, col, 0, 0);
   vtx[1] = AllegroFlare::build_vertex(end.x, end.y, end.z, col, 0, 0);
   al_draw_prim(&vtx[0], NULL, NULL, 0, 2, ALLEGRO_PRIM_LINE_LIST);
   return;
}


} // namespace Physics
} // namespace AllegroFlare


