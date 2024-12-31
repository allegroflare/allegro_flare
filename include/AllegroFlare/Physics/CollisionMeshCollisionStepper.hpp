#pragma once


#include <AllegroFlare/Physics/CollisionMesh.hpp>
#include <AllegroFlare/Physics/CollisionMeshCollisionStepInfo.hpp>
#include <AllegroFlare/Physics/CollisionMeshFace.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Physics
   {
      class CollisionMeshCollisionStepper
      {
      public:
         static constexpr float DEFAULT_AIR_DRAG = 0.06;
         static constexpr float DEFAULT_GRAVITY = -0.016;

      public:

         enum class StepoutStrategy
         {
            STEPOUT_UNDEF = 0,
            STEPOUT_REVERSE_VELOCITY,
            STEPOUT_REFLECT_SURFACE,
            STEPOUT_EXTRUDE_FACE_NORMAL,
            STEPOUT_DIRECTLY_UP,
            STEPOUT_NONE,
         };
         enum class RedirectStrategy
         {
            REDIRECT_UNDEF = 0,
            REDIRECT_REFLECT_SURFACE,
            REDIRECT_COMPLETE_STOP,
            REDIRECT_STOP_VERTICAL,
            REDIRECT_SLIDE_ALONG_SURFACE,
         };
      private:
         AllegroFlare::Physics::CollisionMesh* collision_mesh;
         std::vector<AllegroFlare::Physics::CollisionMesh*> collision_meshes;
         std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* _entities;
         float face_collision_stepout;
         AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy;
         AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy;
         bool apply_environmental_forces;
         float air_drag;
         float gravity;
         std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> collision_step_infos;
         int num_collision_steps;

      protected:


      public:
         CollisionMeshCollisionStepper(AllegroFlare::Physics::CollisionMesh* collision_mesh=nullptr, std::vector<AllegroFlare::Physics::CollisionMesh*> collision_meshes={}, std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* _entities=nullptr, float face_collision_stepout=0.001f);
         ~CollisionMeshCollisionStepper();

         void set_collision_mesh(AllegroFlare::Physics::CollisionMesh* collision_mesh);
         void set_collision_meshes(std::vector<AllegroFlare::Physics::CollisionMesh*> collision_meshes);
         void set__entities(std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* _entities);
         void set_face_collision_stepout(float face_collision_stepout);
         void set_stepout_strategy(AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy);
         void set_redirect_strategy(AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy);
         void set_air_drag(float air_drag);
         void set_gravity(float gravity);
         void set_num_collision_steps(int num_collision_steps);
         AllegroFlare::Physics::CollisionMesh* get_collision_mesh() const;
         std::vector<AllegroFlare::Physics::CollisionMesh*> get_collision_meshes() const;
         std::vector<std::tuple<AllegroFlare::Vec3D*, AllegroFlare::Vec3D*, void*>>* get__entities() const;
         float get_face_collision_stepout() const;
         AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy get_stepout_strategy() const;
         AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy get_redirect_strategy() const;
         bool get_apply_environmental_forces() const;
         float get_air_drag() const;
         float get_gravity() const;
         std::vector<AllegroFlare::Physics::CollisionMeshCollisionStepInfo> get_collision_step_infos() const;
         int get_num_collision_steps() const;
         int num_collision_step_infos();
         void disable_applying_environmental_forces();
         void enable_applying_environmental_forces();
         static void move_to_time_of_collision_and_react_to_collision(AllegroFlare::Vec3D* position_=nullptr, AllegroFlare::Vec3D* velocity_=nullptr, float time_to_collision=0.0f, AllegroFlare::Vec3D* face_normal_=nullptr, float face_collision_stepout=0.001f, AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy=StepoutStrategy::STEPOUT_REVERSE_VELOCITY, AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy=RedirectStrategy::REDIRECT_SLIDE_ALONG_SURFACE);
         float calculate_collisions(float min_entity_velocity_magnitude=0.001f);
         std::tuple<float, AllegroFlare::Physics::CollisionMeshFace*, void*> find_least_collision_time_and_colliding_entity_and_face(float min_entity_velocity_magnitude=0.001f);
         void apply_gravity_and_air_drag(float total_duration=1.0f);
         void step(float total_duration=1.0f);
         static std::string to_string(AllegroFlare::Physics::CollisionMeshCollisionStepper::StepoutStrategy stepout_strategy=StepoutStrategy::STEPOUT_UNDEF);
         static std::string to_string(AllegroFlare::Physics::CollisionMeshCollisionStepper::RedirectStrategy redirect_strategy=RedirectStrategy::REDIRECT_UNDEF);
         static void draw_3d_line(AllegroFlare::Vec3D start={}, AllegroFlare::Vec3D end={}, ALLEGRO_COLOR col=ALLEGRO_COLOR{1, 0, 0, 1});
      };
   }
}



