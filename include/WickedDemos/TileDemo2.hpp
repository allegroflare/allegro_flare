#pragma once


#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/TileMaps/Basic2D.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualControls.hpp>
#include <AllegroFlare/VirtualControlsProcessor.hpp>
#include <Wicked/CameraControlStrategies2D/Base.hpp>
#include <Wicked/Entities/Basic2D.hpp>
#include <Wicked/Weapons/DrawnBow.hpp>
#include <string>
#include <vector>


namespace WickedDemos
{
   class TileDemo2 : public AllegroFlare::Screens::Base
   {
   private:
      AllegroFlare::Frameworks::Full* framework;
      AllegroFlare::Display* display;
      AllegroFlare::EventEmitter* event_emitter;
      int native_display_resolution_width;
      int native_display_resolution_height;
      bool initialized;
      AllegroFlare::TileMaps::Basic2D* currently_active_map;
      std::string currently_active_map_name;
      std::vector<Wicked::Entities::Basic2D*> entities;
      float gravity;
      bool gravity_reversed;
      AllegroFlare::Placement2D camera;
      AllegroFlare::Placement2D hud_projection;
      bool show_tile_mesh;
      bool show_collision_tile_mesh;
      AllegroFlare::VirtualControls player_controls;
      AllegroFlare::VirtualControlsProcessor virtual_controls_processor;
      bool showing_player_reticle;
      AllegroFlare::vec2d player_reticle_vector;
      Wicked::Weapons::DrawnBow bow;
      Wicked::CameraControlStrategies2D::Base* camera_control_strategy;
      int player_collected_items;
      void setup_camera();

   protected:


   public:
      TileDemo2(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::Display* display=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr);
      virtual ~TileDemo2();

      void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
      void set_entities(std::vector<Wicked::Entities::Basic2D*> entities);
      void set_show_tile_mesh(bool show_tile_mesh);
      void set_show_collision_tile_mesh(bool show_collision_tile_mesh);
      void set_showing_player_reticle(bool showing_player_reticle);
      void set_player_reticle_vector(AllegroFlare::vec2d player_reticle_vector);
      bool get_show_tile_mesh() const;
      bool get_show_collision_tile_mesh() const;
      bool get_showing_player_reticle() const;
      AllegroFlare::vec2d get_player_reticle_vector() const;
      std::vector<Wicked::Entities::Basic2D*> &get_entities_ref();
      void set_currently_active_map(std::string name="[unset-current-map-name-to-use]");
      AllegroFlare::TileMaps::Basic2D* find_map_by_name(std::string name="[unset-map-name]");
      void initialize_maps();
      void initialize_hud();
      void initialize_display_projection();
      void initialize_camera_control();
      void initialize();
      void setup_orthographic_projection_on_backbuffer();
      static void run(std::vector<std::string> args={});
      void update();
      void draw_dimentional_grid(float x=0.0f, float y=0.0f, float z=0.0f);
      virtual void primary_timer_func() override;
      void render_collision_tile_mesh();
      AllegroFlare::TileMaps::PrimMeshAtlas* get_tile_atlas();
      AllegroFlare::TileMaps::PrimMesh* get_tile_mesh();
      AllegroFlare::TileMaps::TileMap<int>* get_collision_tile_mesh();
      std::vector<Wicked::Entities::Basic2D*>& get_current_map_entities_ref();
      std::vector<Wicked::Entities::Basic2D*> get_current_map_entities();
   };
}



