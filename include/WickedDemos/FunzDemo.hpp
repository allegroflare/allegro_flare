#pragma once


#include <cmath> // for sin, cos
#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
//#include <Wicked/Inventory.hpp>
#include <Wicked/LevelLoader.hpp>
#include <Wicked/PlayerControl.hpp>
#include <Wicked/SceneFactory.hpp>
#include <Wicked/SceneRenderer.hpp>
#include <Wicked/Light.hpp>

//#include <Tileo/Atlas.hpp>
//#include <Tileo/Mesh.hpp>
#include <AllegroFlare/Random.hpp>
//#include <AllegroFlare/Screen.hpp> //
#include <AllegroFlare/Screens/Base.hpp> //
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Motion.hpp>
//#include <AllegroFlare/Motion.hpp>

#include <AllegroFlare/Display.hpp> //
//#include <AllegroFlare/Framework.hpp> //
#include <AllegroFlare/Frameworks/Full.hpp> //

//using AllegroFlare::Screen;
using AllegroFlare::SampleBin;
using AllegroFlare::FontBin;
//using AllegroFlare::Display;
using AllegroFlare::Motion;
using AllegroFlare::Placement3D;
//using AllegroFlare::Screen;
using AllegroFlare::Display;


#include <WickedDemos/globals.hpp>



#include <WickedDemos/ControlStrategyBase.hpp>


class FunzDemo;


#include <WickedDemos/WorldBuildingControlStrategy.hpp>



class PlayerControlControlStrategy : public ControlStrategyBase
{
private:
   FunzDemo *funz_demo;

public:
   PlayerControlControlStrategy(FunzDemo *funz_demo=nullptr);

   virtual void on_activate() override;
   virtual void on_deactivate() override;

   virtual void key_up_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_down_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void key_char_func(ALLEGRO_EVENT *ev=nullptr) override;
   virtual void primary_timer_func() override;
};


#include <WickedDemos/InventoryControlStrategy.hpp>




class FunzDemo : public AllegroFlare::Screens::Base
{
public:
   // bins
   AllegroFlare::Frameworks::Full *framework;
   AllegroFlare::Display *display;

   AllegroFlare::InventoryIndex inventory_index;
   ALLEGRO_BITMAP *backbuffer_sub_bitmap;

   BitmapBin bitmap_bin;
   SampleBin sample_bin;
   FontBin font_bin;
   AllegroFlare::Random random;


   ModelRepository model_repository;
   EntityFactory entity_factory;

   Wicked::SceneRenderer scene_renderer;
   Motion motion;

   PlayerControl player_control;

   int cursor_over_entity_id;
   int cursor_brush_id;

   static float min_zoom;
   static float max_zoom;

   // assets
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

   AllegroFlare::Sound *cursor_move;
   AllegroFlare::Sound *rotate_selection_sound;
   AllegroFlare::Sound *input_bonk_sound;
   AllegroFlare::Sound *delete_item_sound;
   AllegroFlare::Sound *menu_cursor_move_click_sound;

   ALLEGRO_BITMAP *hud_surface;

   AllegroFlare::Inventory af_inventory;
   //Wicked::Inventory inventory;
   AllegroFlare::Elements::Inventory inventory;
   int input_mode;


   //Tileo::Atlas atlas;
   //Tileo::Mesh mesh;
   


   static void run();


   ControlStrategyBase *control_strategy;


   FunzDemo(AllegroFlare::Frameworks::Full *framework=nullptr, Display *display=nullptr);
   ~FunzDemo();

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
   //virtual void key_up_func(); // override;
   //virtual void key_down_func(); // override;
   //virtual void key_char_func(); // override;

   void primary_timer_func(); // override;
};







