#pragma once


#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualController.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <AllegroFlare/VirtualControlsProcessor.hpp>
#include <Wicked/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Weapons/DrawnBow.hpp>
#include <WickedDemos/TileMaps/Basic2D.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace WickedDemos
{
   class TileDemo : public AllegroFlare::Screens::Base
   {
   private:
      AllegroFlare::Frameworks::Full* framework;
      AllegroFlare::Display* display;
      AllegroFlare::EventEmitter* event_emitter;
      int native_display_resolution_width;
      int native_display_resolution_height;
      bool initialized;
      WickedDemos::TileMaps::Basic2D* currently_active_map;
      std::string currently_active_map_name;
      std::vector<Wicked::Entities::Basic2D*> entities;
      float gravity;
      bool gravity_reversed;
      AllegroFlare::Placement2D camera;
      AllegroFlare::Placement2D hud_projection;
      Wicked::Entities::Basic2D* player_controlled_entity;
      bool show_tile_mesh;
      bool show_collision_tile_mesh;
      AllegroFlare::VirtualController player_controls;
      AllegroFlare::VirtualControlsProcessor XXvirtual_controls_processor;
      bool showing_player_reticle;
      AllegroFlare::vec2d player_reticle_vector;
      Wicked::Weapons::DrawnBow bow;
      Wicked::CameraControlStrategies2D::Base* camera_control_strategy;
      int player_collected_items;
      void setup_camera();
      void initialize_entities();

   protected:


   public:
      TileDemo(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::Display* display=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
      virtual ~TileDemo();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_entities(std::vector<Wicked::Entities::Basic2D*> entities);
      void set_player_controlled_entity(Wicked::Entities::Basic2D* player_controlled_entity);
      void set_show_tile_mesh(bool show_tile_mesh);
      void set_show_collision_tile_mesh(bool show_collision_tile_mesh);
      void set_showing_player_reticle(bool showing_player_reticle);
      void set_player_reticle_vector(AllegroFlare::vec2d player_reticle_vector);
      Wicked::Entities::Basic2D* get_player_controlled_entity() const;
      bool get_show_tile_mesh() const;
      bool get_show_collision_tile_mesh() const;
      bool get_showing_player_reticle() const;
      AllegroFlare::vec2d get_player_reticle_vector() const;
      std::vector<Wicked::Entities::Basic2D*> &get_entities_ref();
      void set_currently_active_map(std::string name="[unset-current-map-name-to-use]");
      WickedDemos::TileMaps::Basic2D* find_map_by_name(std::string name="[unset-map-name]");
      void initialize_display_projection();
      void initialize_maps();
      void initialize_hud();
      void setup_projection();
      void initialize_camera_control();
      void initialize_player_controls();
      void initialize();
      void setup_orthographic_projection_on_backbuffer();
      void unset_player_controlled_entity_vertical_velocity();
      void unset_player_controlled_entity_horizontal_velocity();
      void set_player_controlled_entity_jump();
      void player_emit_projectile(float magnitude=3.0f);
      void reverse_gravity();
      void update_entities();
      void delete_entities_flagged_for_deletion();
      void check_player_collisions_with_doors();
      void update_player_collisions_with_collectables();
      void update_player_collisions_with_goalposts();
      void player_increment_collected_items();
      void draw_entities();
      void draw_hud();
      static void run(std::vector<std::string> args={});
      void update_player_controls_on_player_controlled_entity();
      void update();
      void draw_dimensional_grid(float x=0.0f, float y=0.0f, float z=0.0f);
      void draw();
      void draw_player_reticle();
      void toggle_show_collision_tile_mesh();
      void toggle_show_tile_mesh();
      virtual void primary_timer_func() override;
      virtual void __primary_timer_func();
      virtual void key_char_func(ALLEGRO_EVENT* event=nullptr) override;
      virtual void _joy_button_down_func(ALLEGRO_EVENT* event=nullptr);
      virtual void _joy_button_up_func(ALLEGRO_EVENT* event=nullptr);
      virtual void _joy_axis_func(ALLEGRO_EVENT* event=nullptr);
      virtual void _key_up_func(ALLEGRO_EVENT* event=nullptr);
      virtual void _key_down_func(ALLEGRO_EVENT* event=nullptr);
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
      std::vector<Wicked::Entities::Basic2D*>& get_current_map_entities_ref();
      std::vector<Wicked::Entities::Basic2D*> get_current_map_entities();
   };
}



