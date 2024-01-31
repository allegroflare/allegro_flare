#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera2D.hpp>
#include <AllegroFlare/CameraControlStrategies2D/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoaderObjectCustomProperties.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class Screen : public AllegroFlare::Screens::Gameplay
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Prototypes/Platforming2D/Screen";

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::EventEmitter* event_emitter;
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
            bool show_visual_hint_on_suspended_gameplay;
            AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base* entity_control_connector;
            AllegroFlare::CameraControlStrategies2D::Base* camera_control_strategy;
            std::function<void( std::string, float, float, float, float, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > create_entities_from_map_callback;
            void* create_entities_from_map_callback_user_data;
            bool initialized;
            bool maps_initialized;
            void initialize_camera();
            void cleanup_entities_flagged_for_deletion();
            void check_player_collisions_with_doors();
            void update_player_collisions_with_collectables();
            void update_player_collisions_with_goalposts();

         protected:


         public:
            Screen(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
            virtual ~Screen();

            void set_entity_pool(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entity_pool);
            void set_camera_baseline_zoom(AllegroFlare::Vec2D camera_baseline_zoom);
            void set_show_tile_mesh(bool show_tile_mesh);
            void set_show_collision_tile_mesh(bool show_collision_tile_mesh);
            void set_show_visual_hint_on_suspended_gameplay(bool show_visual_hint_on_suspended_gameplay);
            void set_entity_control_connector(AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base* entity_control_connector);
            void set_create_entities_from_map_callback(std::function<void( std::string, float, float, float, float, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > create_entities_from_map_callback);
            void set_create_entities_from_map_callback_user_data(void* create_entities_from_map_callback_user_data);
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::EventEmitter* get_event_emitter() const;
            std::map<std::string, std::string> get_map_dictionary() const;
            AllegroFlare::Vec2D get_camera_baseline_zoom() const;
            AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* get_player_controlled_entity() const;
            bool get_show_tile_mesh() const;
            bool get_show_collision_tile_mesh() const;
            bool get_show_visual_hint_on_suspended_gameplay() const;
            AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base* get_entity_control_connector() const;
            std::function<void( std::string, float, float, float, float, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > get_create_entities_from_map_callback() const;
            void* get_create_entities_from_map_callback_user_data() const;
            void set_map_dictionary(std::map<std::string, std::string> map_dictionary={});
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_currently_active_map(std::string name="[unset-current-map-name-to-use]");
            void set_player_controlled_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr, bool also_set_as_camera_tracked_object=true, bool also_setup_a_basic2d_entity_control_connector=true);
            AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* find_map_by_name(std::string name="[unset-map-name]");
            virtual void on_activate() override;
            virtual void on_deactivate() override;
            void initialize_maps();
            void initialize_camera_control();
            void initialize();
            void add_entity_to_pool(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity=nullptr);
            void player_emit_projectile(float magnitude=3.0f);
            void reverse_gravity();
            void update_entities();
            void draw_entities();
            void update();
            void draw();
            void toggle_show_collision_tile_mesh();
            void toggle_show_tile_mesh();
            virtual void primary_update_func(double time_now=0.0, double delta_time=0.0) override;
            virtual void primary_render_func() override;
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



