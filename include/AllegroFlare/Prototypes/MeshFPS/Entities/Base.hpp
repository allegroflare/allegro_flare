#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/PlayerInputControllers/Base.hpp>
#include <AllegroFlare/Prototypes/MeshFPS/Entities/Base.hpp>
#include <AllegroFlare/SceneGraph/Entities/Base.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MeshFPS
      {
         namespace Entities
         {
            class Base : public AllegroFlare::SceneGraph::Entities::Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/MeshFPS/Entities/Base";

            private:
               std::string type;
               AllegroFlare::Model3D* model;
               ALLEGRO_BITMAP* texture;
               AllegroFlare::Placement3D placement;
               AllegroFlare::Placement3D velocity;
               AllegroFlare::Physics::AABB2D hit_box_2d;
               AllegroFlare::PlayerInputControllers::Base* player_input_controller;

            protected:


            public:
               std::vector<AllegroFlare::Vec3D> box_corners;
               bool active;
               bool visible;
               bool affected_by_environmental_forces;
               bool collides_with_environment;
               bool collides_with_player;
               bool collides_with_enemies;
               Base(std::string type=AllegroFlare::Prototypes::MeshFPS::Entities::Base::TYPE, AllegroFlare::Model3D* model=nullptr, ALLEGRO_BITMAP* texture=nullptr, AllegroFlare::Placement3D placement={}, AllegroFlare::Placement3D velocity={}, AllegroFlare::Physics::AABB2D hit_box_2d={}, AllegroFlare::PlayerInputControllers::Base* player_input_controller=nullptr);
               virtual ~Base();

               void set_type(std::string type);
               void set_model(AllegroFlare::Model3D* model);
               void set_texture(ALLEGRO_BITMAP* texture);
               void set_placement(AllegroFlare::Placement3D placement);
               void set_velocity(AllegroFlare::Placement3D velocity);
               void set_hit_box_2d(AllegroFlare::Physics::AABB2D hit_box_2d);
               void set_player_input_controller(AllegroFlare::PlayerInputControllers::Base* player_input_controller);
               std::string get_type() const;
               AllegroFlare::Model3D* get_model() const;
               ALLEGRO_BITMAP* get_texture() const;
               AllegroFlare::Placement3D get_placement() const;
               AllegroFlare::Placement3D get_velocity() const;
               AllegroFlare::Physics::AABB2D get_hit_box_2d() const;
               AllegroFlare::PlayerInputControllers::Base* get_player_input_controller() const;
               AllegroFlare::Placement3D &get_placement_ref();
               AllegroFlare::Placement3D &get_velocity_ref();
               AllegroFlare::Physics::AABB2D &get_hit_box_2d_ref();
               AllegroFlare::PlayerInputControllers::Base* &get_player_input_controller_ref();
               bool has_player_input_controller();
               virtual void destroy();
               virtual void on_time_step(double time_step=0.0f, double time_now=0.0f);
               virtual void on_tile_map_collision_stepper_step(AllegroFlare::Physics::TileMapCollisionStepperStepResult* collision_step_result=nullptr);
               virtual void on_enter_player_bbox_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity=nullptr);
               virtual void on_exit_player_bbox_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity=nullptr);
               virtual void on_enter_player_position_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity=nullptr);
               virtual void on_exit_player_position_collision(AllegroFlare::Prototypes::MeshFPS::Entities::Base* player_entity=nullptr);
               virtual void on_player_inspect_or_use();
               bool collides(AllegroFlare::Prototypes::MeshFPS::Entities::Base* other=nullptr);
               void calculate_box_corners();
               ALLEGRO_COLOR build_color(float opacity=1.0f);
               std::vector<ALLEGRO_VERTEX> build_line_list_vertices();
               std::vector<ALLEGRO_VERTEX> build_triangle_list_vertices_for_faces();
            };
         }
      }
   }
}



