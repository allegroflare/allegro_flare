#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualController.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::Display* display;
            AllegroFlare::EventEmitter* event_emitter;
            int native_display_resolution_width;
            int native_display_resolution_height;
            bool initialized;
            AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* currently_active_map;
            std::string currently_active_map_name;
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entity_pool;
            std::map<std::string, std::string> map_dictionary;
            float gravity;
            bool gravity_reversed;
            AllegroFlare::Camera2D camera;
            AllegroFlare::Vec2D camera_baseline_zoom;
            AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity;
            bool show_tile_mesh;
            bool show_collision_tile_mesh;
            bool gameplay_suspended;
            AllegroFlare::VirtualController player_controls;
            AllegroFlare::CameraControlStrategies2D::Base* camera_control_strategy;
            ALLEGRO_BITMAP* backbuffer_sub_bitmap;
            void initialize_camera();
            void cleanup_entities_flagged_for_deletion();
            void check_player_collisions_with_doors();
            void update_player_collisions_with_collectables();
            void update_player_collisions_with_goalposts();

         protected:


         public:
            Screen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::Display* display=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
            virtual ~Screen();

            void set_entity_pool(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entity_pool);
            void set_camera_baseline_zoom(AllegroFlare::Vec2D camera_baseline_zoom);
            void set_player_controlled_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity);
            void set_show_tile_mesh(bool show_tile_mesh);
            void set_show_collision_tile_mesh(bool show_collision_tile_mesh);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            std::map<std::string, std::string> get_map_dictionary() const;
            AllegroFlare::Vec2D get_camera_baseline_zoom() const;
            AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* get_player_controlled_entity() const;
            bool get_show_tile_mesh() const;
            bool get_show_collision_tile_mesh() const;
            bool get_gameplay_suspended() const;
            void set_map_dictionary(std::map<std::string, std::string> map_dictionary={});
            void set_display(AllegroFlare::Display* display=nullptr);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_currently_active_map(std::string name="[unset-current-map-name-to-use]");
            AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* find_map_by_name(std::string name="[unset-map-name]");
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            void initialize_maps();
            void add_entity_to_pool(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr);
            void initialize_camera_control();
            void initialize_player_controls();
            void initialize_backbuffer_sub_bitmap();
            void initialize();
            void unset_player_controlled_entity_vertical_velocity();
            void unset_player_controlled_entity_horizontal_velocity();
            void set_player_controlled_entity_jump();
            void player_emit_projectile(float magnitude=3.0f);
            void reverse_gravity();
            void update_entities();
            void draw_entities();
            void update_player_controls_on_player_controlled_entity();
            void suspend_gameplay();
            void resume_suspended_gameplay();
            void update();
            void draw();
            void toggle_show_collision_tile_mesh();
            void toggle_show_tile_mesh();
            virtual void primary_timer_func() override;
            virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_up_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_button_up_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
            virtual void virtual_control_axis_change_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void user_event_func(ALLEGRO_EVENT* event=nullptr) override;
            void render_collision_tile_mesh();
            AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas();
            AllegroFlare::TileMaps::PrimMesh* get_tile_mesh();
            AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_mesh();
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> get_current_map_entities();
         };
      }
   }
}



