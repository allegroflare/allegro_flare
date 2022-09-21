#pragma once


#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Motion.hpp>
#include <AllegroFlare/Display.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>

#include <Wicked/PlayerControl.hpp>
#include <Wicked/SceneRenderer.hpp>
#include <Wicked/Light.hpp>

#include <WickedDemos/EntityFactory.hpp>
#include <WickedDemos/ModelRepository.hpp>
#include <WickedDemos/ControlStrategyBase.hpp>



class FunzDemo : public AllegroFlare::Screens::Base
{
public:
   AllegroFlare::Frameworks::Full *framework;
   AllegroFlare::Display *display;
   ALLEGRO_BITMAP *backbuffer_sub_bitmap;
   AllegroFlare::BitmapBin *bitmap_bin;
   AllegroFlare::SampleBin *sample_bin;
   AllegroFlare::FontBin *font_bin;
   AllegroFlare::Random random;
   ModelRepository model_repository;
   EntityFactory entity_factory;
   Wicked::SceneRenderer scene_renderer;
   AllegroFlare::Motion motion;
   PlayerControl player_control;
   int cursor_over_entity_id;
   int cursor_brush_id;
   static float min_zoom;
   static float max_zoom;
   AllegroFlare::Camera3D camera;
   ShadowCastingLight casting_light;
   Light light;
   vec2d texture_offset;
   ALLEGRO_TRANSFORM shadow_map_depth_pass_transform;
   ALLEGRO_BITMAP *shadow_map_depth_pass_surface;
   Entity *skybox;
   Entity *pointer;
   std::vector<Entity *> entities;
   bool camera_spinning;
   float light_time_of_day;
   float light_target_time_of_day;
   float light_spin;
   float light_target_spin;
   float camera_target_spin;
   float camera_target_stepout_z;
   vec3d camera_target_position;
   float camera_target_zoom;
   //AllegroFlare::Sound *cursor_move;
   //AllegroFlare::Sound *rotate_selection_sound;
   //AllegroFlare::Sound *input_bonk_sound;
   //AllegroFlare::Sound *delete_item_sound;
   //AllegroFlare::Sound *menu_cursor_move_click_sound;
   ALLEGRO_BITMAP *hud_surface;
   AllegroFlare::InventoryIndex inventory_index;
   AllegroFlare::Inventory af_inventory;
   AllegroFlare::Elements::Inventory inventory;
   int input_mode;
   ControlStrategyBase *control_strategy;
   bool initialized;

   FunzDemo(AllegroFlare::Frameworks::Full *framework=nullptr, AllegroFlare::Display *display=nullptr);
   ~FunzDemo();

   static void run();
   void initialize();
   void set_targets_to_currents();
   void rescale_entity_ids();
   void toggle_inventory();
   bool basic_collide(Entity *entity, vec3d point, float padding); // TODO this was never finished
   void update_to_target(float &source, float target, float step_percentage = 0.1f);
   Entity *find_by_id(int id);
   void update_selected();
   void update_camera_position_to_target();
   void update_scene_physics();
   void draw_scene();
   void draw_hud();
   std::string random_string(int length);
   void setup_input_mode(int new_input_mode);
   virtual void key_up_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_down_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_char_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void primary_timer_func() override;
};






