#include <WickedDemos/FunzDemo.hpp>

#include <AllegroFlare/Useful.hpp>
#include <WickedDemos/globals.hpp>

#include <cmath> // for sin, cos
#include <AllegroFlare/Placement3D.hpp>
#include <Wicked/LevelLoader.hpp>
#include <Wicked/SceneFactory.hpp>

#include <WickedDemos/WorldBuildingControlStrategy.hpp>
#include <WickedDemos/InventoryControlStrategy.hpp>
#include <WickedDemos/PlayerControlControlStrategy.hpp>


FunzDemo::FunzDemo(AllegroFlare::Frameworks::Full *framework, AllegroFlare::Display *display)
   : AllegroFlare::Screens::Base("FunzDemo")
   , framework(framework)
   , display(display)
   , backbuffer_sub_bitmap(nullptr)
   , bitmap_bin(nullptr)
   , sample_bin(nullptr)
   , font_bin(nullptr)
   , random()
   , model_repository()
   , entity_factory() // 
   , scene_renderer() // 
   , motion()
   , player_control()
   , cursor_over_entity_id(0)
   , cursor_brush_id(CURSOR_BRUSH_CUBE)
   , showing_shadow_render(false)
   //static float min_zoom;
   //static float max_zoom;
   , camera()
   , casting_light() //
   , light(4, 4, 3) //
   , texture_offset(0, 0)
   , shadow_map_depth_pass_transform()
   , shadow_map_depth_pass_surface(nullptr) //
   , skybox(nullptr) //
   , pointer(nullptr) //
   , entities()
   , camera_spinning(true)
   , light_time_of_day(0.15)
         // 0.05; // sunrise
         // 0.5; // high noon
         // 0.95; // sunset
   , light_target_time_of_day(light_time_of_day)
   , light_spin(0.0)
   , light_target_spin(0.0)
   , camera_target_spin(0.0)
   , camera_target_stepout_z(0.0)
   , camera_target_position(0, 0, 0)
   , camera_target_zoom(1.0)
   //, cursor_move(nullptr)
   //, rotate_selection_sound(nullptr)
   //, input_bonk_sound(nullptr)
   //, delete_item_sound(nullptr)
   //, menu_cursor_move_click_sound(nullptr)
   , hud_surface(nullptr)
   , inventory_index()
   , af_inventory()
   , inventory() // &font_bin, &bitmap_bin, &af_inventory, &inventory_index, nullptr)
   , input_mode(INPUT_MODE_WORLD_BUILDING)
   , control_strategy(nullptr)
   , initialized(false)
{
}




void FunzDemo::run(float seconds_to_timeout)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   FunzDemo *funz_demo = new FunzDemo(&framework, framework.get_primary_display());
   funz_demo->initialize();

   framework.register_and_activate_screen("funz_demo", funz_demo);
   //framework.activate_screen("funz_demo");

   framework.run_loop(seconds_to_timeout);
   //framework.unregister_screen(funz_demo);

   //delete funz_demo;
}



FunzDemo::~FunzDemo()
{
   //if (cursor_move) delete cursor_move;
   //if (rotate_selection_sound) delete rotate_selection_sound;
   //if (input_bonk_sound) delete input_bonk_sound; 
   //if (delete_item_sound) delete delete_item_sound;
   //if (menu_cursor_move_click_sound) delete menu_cursor_move_click_sound;
}


void FunzDemo::initialize()
{
   if (initialized)
   {
      std::stringstream error_message;
      error_message << "WickedDemos::FunzDemo error: Cannot initialize more than once." << std::endl;
      throw std::runtime_error(error_message.str());
   }

   if (!framework)
   {
      std::stringstream error_message;
      error_message << "WickedDemos::FunzDemo error: framework cannot be nullptr." << std::endl;
      throw std::runtime_error(error_message.str());
   }


   font_bin = &framework->get_font_bin_ref();
   sample_bin = &framework->get_sample_bin_ref();
   bitmap_bin = &framework->get_bitmap_bin_ref();


   bitmap_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");
   sample_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/samples");
   font_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");



   //inventory() // &font_bin, &bitmap_bin, &af_inventory, &inventory_index, nullptr)
   inventory.set_font_bin(&framework->get_font_bin_ref());
   inventory.set_bitmap_bin(&framework->get_bitmap_bin_ref());
   inventory.set_af_inventory(&af_inventory);
   inventory.set_inventory_index(&inventory_index);
   inventory.set_event_emitter(&framework->get_event_emitter_ref());



   scene_renderer.initialize();


   // activate a control strategy
   if (control_strategy) control_strategy->on_deactivate();
   control_strategy = new WorldBuildingControlStrategy(this);
   control_strategy->on_activate();


   // initialize the bins
   //bitmap_bin.set_path("data/bitmaps");
   //sample_bin.set_path("data/samples");
   //font_bin.set_path("data/fonts");

   // NOTE, TODO, these assets are being stored in a location different from the rest of where the typical assets
   // are stored with allegro_flare
   //bitmap_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");
   //sample_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/samples");
   //font_bin->set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");

   // preload the assets
   //sample_bin->preload("cursor-move-01.ogg");
   //sample_bin->preload("rotate-selection-01.ogg");
   //sample_bin->preload("ui-input-bonk-01.ogg");
   //sample_bin->preload("delete-item-01.ogg");
   //sample_bin->preload("menu-click-01.ogg");

   //cursor_move = new AllegroFlare::Sound(sample_bin["cursor-move-01.ogg"]);
   //rotate_selection_sound = new AllegroFlare::Sound(sample_bin["rotate-selection-01.ogg"]);
   //input_bonk_sound = new AllegroFlare::Sound(sample_bin["ui-input-bonk-01.ogg"]);
   //delete_item_sound = new AllegroFlare::Sound(sample_bin["delete-item-01.ogg"]);
   //menu_cursor_move_click_sound = new AllegroFlare::Sound(sample_bin["menu-click-01.ogg"]);

   font_bin->preload("ui-font", "SourceSerif4_18pt-SemiBoldItalic.ttf -20");
   font_bin->preload("SourceSerif4_18pt-SemiBoldItalic.ttf -80");
   font_bin->preload("SourceSerif4_18pt-SemiBoldItalic.ttf -30");


   // NOTE:: removed usage of the backbuffer_bitmap (unknown consequences)
   // MARK
   ALLEGRO_BITMAP *backbuffer_sub_bitmap_target = al_get_backbuffer(al_get_current_display());
   backbuffer_sub_bitmap = al_create_sub_bitmap(backbuffer_sub_bitmap_target,
      0, 0, al_get_bitmap_width(backbuffer_sub_bitmap_target), al_get_bitmap_height(backbuffer_sub_bitmap_target));

   //create_and_use_backbuffer_sub_bitmap_of(al_get_backbuffer(al_get_current_display()));


   model_repository.initialize();
   entity_factory.initialize();
   scene_renderer.set_backbuffer_sub_bitmap(backbuffer_sub_bitmap);
   scene_renderer.set_shadow_scale_divisor(1.0); // note, increasing this divisor will
   //scene_renderer.set_shadow_scale_divisor(1.0); // note, increasing this divisor will
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but reduce
      // the resolution of the shadow. Original engine had a default of 1.0f;

   //motion.initialize();



   //const std::string TILE_MAP_BITMAP = "tiles_dungeon_v1.1.png";
   //ALLEGRO_STATE previous_bitmap_state;
   //al_store_state(&previous_bitmap_state, ALLEGRO_STATE_NEW_BITMAP_PARAMETERS);
   //al_set_new_bitmap_flags(0);
   //bitmap_bin.preload(TILE_MAP_BITMAP);
   //atlas.duplicate_bitmap_and_load(bitmap_bin[TILE_MAP_BITMAP], 16, 16);
   //al_restore_state(&previous_bitmap_state);

   //mesh.initialize();
   //AllegroFlare::Random random;
   //for (int y=0; y<mesh.get_num_rows(); y++)
   //{
      //for (int x=0; x<mesh.get_num_columns(); x++)
      //{
         //int random_tile = random.get_random_int(0, atlas.get_tile_index_size());
         ////int random_tile = 4 + (5 * mesh.get_num_columns());
         //mesh.set_tile(x, y, random_tile);
      //}
   //}



   al_identity_transform(&shadow_map_depth_pass_transform);

   //camera.stepout = vec3d(0, 1.5, 8);
   camera.stepout = vec3d(0, 0, 10);
   camera.tilt = 0.6;
   camera_target_stepout_z = camera.stepout.z;
   camera_target_position = camera.position;
   camera_target_zoom = camera.zoom;


   shadow_map_depth_pass_surface = al_create_bitmap(display->get_width(), display->get_height());
   hud_surface =
      al_create_sub_bitmap(al_get_backbuffer(display->al_display), 0, 0, display->get_width(), display->get_height());

   //inventory.scale_for(al_get_bitmap_width(hud_surface), al_get_bitmap_height(hud_surface));
   // ^^ NOTE: not sure what this is for
   std::cout <<
      "WARNING: FunzDemo::initialize() bypassing inventory.scale_for(..). This could cause the inventory window "
      "to not appear properly." << std::endl;



   // TODO: note this is a cheap replacement for the map in globls.hpp
   //inventory_index = AllegroFlare::InventoryIndex::build_placeholder_inventory_index();
   //std::cout << "WARNING: Building FunzDemo::inventory_index with a placeholder index. Please update this index to be filled with the index provided in WickedDemos/globals.cpp, thank you." << std::endl;

   inventory_index = AllegroFlare::InventoryIndex(CREATORS_INVENTORY_INDEX2);

   inventory.set_event_emitter(&framework->get_event_emitter_ref());


   for (auto &inventory_dictionary_item : CREATORS_INVENTORY_INDEX2)
   {
      af_inventory.add_item(inventory_dictionary_item.first);
   }





   SceneFactory scene_factory;


   pointer = entity_factory.create_pointer();
   
   //scene_factory.construct_scene(&entities, entity_factory, &skybox);
   scene_factory.load_level_from_file(
      &entities,
      entity_factory,
      &skybox,
      "/Users/markoates/Repos/allegro_flare/bin/data/worlds/world-with-boxes-01.json",
      camera,
      casting_light
   );

   rescale_entity_ids();
   set_targets_to_currents();



   //LevelLoader level_loader;
   //level_loader.write(&entities, light_target_time_of_day);


   initialized = true;

}


void FunzDemo::set_targets_to_currents()
{
   //light_time_of_day;
   //light_target_time_of_day;
   light_spin = casting_light.spin;
   light_target_spin = casting_light.spin;

   camera_target_spin = camera.spin;
   camera_target_stepout_z = camera.stepout.z;
   camera_target_position = camera.position;
   camera_target_zoom = camera.zoom;
}


void FunzDemo::rescale_entity_ids()
{
   for (int i=0; i<(int)entities.size(); i++) { entities[i]->__set_id(i); }
   Entity::__set_next_id(entities.size());
}


void FunzDemo::toggle_inventory()
{
   if (inventory.get_active()) inventory.hide();
   else inventory.show();
}


bool FunzDemo::basic_collide(Entity *entity, vec3d point, float padding) // TODO this was never finished
{
   if (!entity) return false;
   vec3d &entity_position = entity->place.position;
   if (entity_position.x < point.x - padding) return false;
   if (entity_position.x > point.x + padding) return false;
   if (entity_position.y < point.y - padding) return false;
   if (entity_position.y > point.y + padding) return false;
   if (entity_position.z < point.z - padding) return false;
   if (entity_position.z > point.z + padding) return false;
   return true;
}


void FunzDemo::update_to_target(float &source, float target, float step_percentage)
{
   if (target != source)
   {
      float diff = target - source;
      source += diff * step_percentage;
   }
}


Entity *FunzDemo::find_by_id(int id)
{
   for (auto &entity : entities) { if (entity->get_id() == id) return entity; }
   return nullptr;
}


void FunzDemo::update_selected()
{
   // unselect all
   for (auto &entity : entities)
   {
      entity->is_selected_with_cursor = false;
   }

   // select current entity id
   Entity *entity = find_by_id(cursor_over_entity_id);
   if (entity) entity->is_selected_with_cursor = true;
}


void FunzDemo::update_camera_position_to_target()
{
   //motion.update(al_get_time());

   // update_the_time_of_day
   if (light_time_of_day != light_target_time_of_day)
   {
      float diff = light_target_time_of_day - light_time_of_day;
      light_time_of_day += diff * 0.1;
   }

   if (camera_target_spin != camera.spin)
   {
      float diff = camera_target_spin - camera.spin;
      camera.spin += diff * 0.1;
   }

   if (camera_target_stepout_z != camera.stepout.z)
   {
      float diff = camera_target_stepout_z - camera.stepout.z;
      camera.stepout.z += diff * 0.1;
   }

   if (camera_target_zoom != camera.zoom)
   {
      float diff = camera_target_zoom - camera.zoom;
      camera.zoom += diff * 0.1;
   }

   // update_player_movement

   update_to_target(camera.position.x, camera_target_position.x, 0.3);
   update_to_target(camera.position.y, camera_target_position.y, 0.3);
   update_to_target(camera.position.z, camera_target_position.z, 0.3);

   update_to_target(light_spin, light_target_spin, 0.15);
}


void FunzDemo::update_scene_physics()
{


   // update light positions
   if (camera_spinning)
   {
      camera.spin += 1.0 / 60.0 * 0.1;
      camera_target_spin = camera.spin;
   }

   //casting_light.spin -= 1.0 / 60.0 * 0.05;
   light.position = casting_light.get_real_position();



   // update entity positions
   for (unsigned i=0; i<entities.size(); i++)
   {
      entities[i]->place.position += entities[i]->velocity.position;
      entities[i]->place.rotation += entities[i]->velocity.rotation;
   }

   
   // uptate pointer
   pointer->place.position += pointer->velocity.position;
   pointer->place.rotation += pointer->velocity.rotation;



   // update the casting light's position (for time of day)
   casting_light.stepout = vec3d(0, 0, 15); // note
                                            // the fustum is currently at (near=30, far=-30),
                                            // so a z stepback of 30 would be right at the edge
                                            // and would bearely (if at all) render objects
                                            // with z==0 world coordinates.  It's recommended
                                            // to keep the stepback about half way, so 15

   //casting_light.stepout = vec3d(0, 1, 33);
   //casting_light.stepout = vec3d(0, 5, 33);
   //casting_light.stepout = vec3d(0, 1.5, 8);
   casting_light.tilt = 3.141592653 * light_time_of_day; // light_time_of_day = 0.05; // sunrise
                                                         //                     0.5; // high noon
                                                         //                     0.95; // sunset

   casting_light.spin = light_spin;
}


//void draw_ground_mesh()
//{
   //float x = 0;
   //float y = 0;
   //float z = 0;

   ////float sx = 1.0 / 16;
   ////float sy = 1.0 / 16;
   ////float sz = 1.0 / 16;

   //ALLEGRO_STATE previous_state;
   //al_store_state(&previous_state, ALLEGRO_STATE_TRANSFORM);

   //float diff = sin(al_get_time());

   //ALLEGRO_TRANSFORM transform;
   //al_identity_transform(&transform);
   ////al_scale_transform_3d(&transform, sx, sy, sz);
   //al_translate_transform_3d(&transform, x-10, y, z-5);
   //al_use_transform(&transform);

   //mesh.render();

   //al_restore_state(&previous_state);
//}


void FunzDemo::draw_scene()
{
   // refresh pre-render textures and set the projection
   scene_renderer.refresh_shadow_map(
      &entities,
      casting_light,
      &shadow_map_depth_pass_transform,
      shadow_map_depth_pass_surface,
      pointer
   );
   camera.setup_projection_on(backbuffer_sub_bitmap);
   //scene_renderer.setup_projection_SCENE(camera, nullptr);

   // draw all the scene elements
   vec3d camera_real_position = camera.get_real_position();
   vec3d camera_looking_at_point = camera_target_position; //camera.position;
   vec3d light_position = light.position * 100.0;
   scene_renderer.draw_entities(
      camera_real_position,
      light_position,
      skybox,
      &entities,
      &shadow_map_depth_pass_transform,
      shadow_map_depth_pass_surface,
      texture_offset,
      pointer,
      camera_looking_at_point
   );


   //draw_ground_mesh();
}


void FunzDemo::draw_hud()
{
   ALLEGRO_FONT *font = nullptr;
   ALLEGRO_STATE tbs;
   al_store_state(&tbs, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_TRANSFORM);

   ALLEGRO_TRANSFORM t;
   al_identity_transform(&t);
   al_set_target_bitmap(hud_surface);
   //al_clear_to_color(al_color_name("pink"));
   //al_use_projection_transform(&t);
   al_set_render_state(ALLEGRO_DEPTH_TEST, 0);

   font = font_bin->auto_get("SourceSerif4_18pt-SemiBoldItalic.ttf -80");
   int num_entity_ids = Entity::get_last_id();

   std::stringstream ss;
   ss << cursor_over_entity_id << " / " << num_entity_ids;

   float pos_x = 80;
   float pos_y = 30;
   float p = 5;
   al_draw_text(font, al_color_name("black"), pos_x-p*0.5, pos_y-p*0.5, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x-p*0.5, pos_y+p*0.5, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x+p*0.5, pos_y+p*0.5, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x+p*0.5, pos_y-p*0.5, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x, pos_y-p, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x+p, pos_y, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x, pos_y+p, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("black"), pos_x-p, pos_y, ALLEGRO_ALIGN_LEFT, ss.str().c_str());
   al_draw_text(font, al_color_name("white"), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, ss.str().c_str());


   std::string text = "brush: " + inventory_index_id_to_factory_identifier(cursor_brush_id);
   al_draw_text(font, al_color_name("white"), pos_x, pos_y + 80, ALLEGRO_ALIGN_LEFT, text.c_str());


   // some shared vars
   float height;


   // draw zoom bar
   height = 400;
   float zoom_cursor_pos = 1.0 - (camera.zoom - min_zoom) / (max_zoom - min_zoom);
   float y_pos = al_get_bitmap_height(hud_surface) * 0.5 - height/2;
   al_draw_line(80, y_pos, 80, y_pos+height, ALLEGRO_COLOR{1,1,1,1}, 4.0);
   al_draw_filled_circle(80, y_pos + height * zoom_cursor_pos, 12, ALLEGRO_COLOR{1, 1, 1, 1});


   // draw inputs
   height = 60;
   float hud_opacity = 0.4;
   ALLEGRO_COLOR backfill_color = ALLEGRO_COLOR{0, 0, 0, hud_opacity};
   al_draw_filled_rectangle(0, al_get_bitmap_height(hud_surface)-height, al_get_bitmap_width(hud_surface), al_get_bitmap_height(hud_surface), backfill_color);

   // draw inputs text
   font = font_bin->auto_get("SourceSerif4_18pt-SemiBoldItalic.ttf -30");
   std::string SPACER = "         ";
   std::string inputs = "[W/A/S/D]  Move cursor"
                      + SPACER + "[N/P]  Next/Previous Entity"
                      + SPACER + "[Shift+8]  Capture screenshot"
                      + SPACER + "[PAD +/-]  Zoom"
                      + SPACER + "[I]  Toggle Inventory"
                      + SPACER + "[-/+]  Change time of day";
   //float text_width = al_get_text_width(font, inputs.str());
   float text_height = al_get_font_line_height(font);
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, al_get_bitmap_width(hud_surface)/2, al_get_bitmap_height(hud_surface)-text_height/2-height/2, ALLEGRO_ALIGN_CENTER, inputs.c_str());



   // code showing timer differentials

   //std::stringstream tticks;
   //tticks << allegro_flare::Framework::timer_tick_times.size();

   //std::stringstream stickss;
   //stickss << allegro_flare::Framework::screen_flip_start_times.size();

   //std::stringstream stickse;
   //stickse << allegro_flare::Framework::screen_flip_end_times.size();

   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, al_get_bitmap_height(hud_surface)-text_height/2-height/2, ALLEGRO_ALIGN_LEFT, tticks.str().c_str());
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 120, al_get_bitmap_height(hud_surface)-text_height/2-height/2, ALLEGRO_ALIGN_LEFT, stickss.str().c_str());
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 220, al_get_bitmap_height(hud_surface)-text_height/2-height/2, ALLEGRO_ALIGN_LEFT, stickse.str().c_str());

   //std::stringstream delta;
   //delta << (AllegroFlare::Framework::timer_tick_times.back() - AllegroFlare::Framework::screen_flip_end_times.back());
   //al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 320, al_get_bitmap_height(hud_surface)-text_height/2-height/2, ALLEGRO_ALIGN_LEFT, delta.str().c_str());


   //render_depth_pass_surface
   if (showing_shadow_render) al_draw_bitmap(shadow_map_depth_pass_surface, 0, 0, 0);



   // draw the inventory
   inventory.render();


   al_restore_state(&tbs);
}


std::string FunzDemo::random_string(int length)
{
   return random.get_random_string(length);
}


void FunzDemo::setup_input_mode(int new_input_mode)
{
   ControlStrategyBase *new_control_strategy = nullptr;

   switch (new_input_mode)
   {
   case INPUT_MODE_WORLD_BUILDING:
      new_control_strategy = new WorldBuildingControlStrategy(this);
      input_mode = INPUT_MODE_WORLD_BUILDING;
      break;
   case INPUT_MODE_PLAYER_CONTROL:
      new_control_strategy = new PlayerControlControlStrategy(this);
      input_mode = INPUT_MODE_PLAYER_CONTROL;
      break;
   case INPUT_MODE_INVENTORY:
      new_control_strategy = new InventoryControlStrategy(this);
      input_mode = INPUT_MODE_INVENTORY;
      break;
   default:
      throw std::runtime_error("unrecognized control stragety");
      break;
   }

   if (new_control_strategy)
   {
      // activate a control strategy
      if (control_strategy)
      {
         control_strategy->on_deactivate();
         delete control_strategy;
      }
      control_strategy = new_control_strategy;
      new_control_strategy->on_activate();
   }
}


void FunzDemo::key_up_func(ALLEGRO_EVENT *ev)// override
{
   //ALLEGRO_EVENT *this_ev = framework->current_event;
   if (control_strategy) control_strategy->key_up_func(ev);
}


void FunzDemo::key_down_func(ALLEGRO_EVENT *ev)// override
{
   //ALLEGRO_EVENT *this_ev = framework->current_event;
   if (control_strategy) control_strategy->key_down_func(ev);
}


void FunzDemo::key_char_func(ALLEGRO_EVENT *ev)// override
{
   // universal keyboard inputs

   //ALLEGRO_EVENT *ev = framework->current_event; //key_down_func();
   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;


   //ALLEGRO_EVENT *this_ev = framework->current_event;
   if (control_strategy) control_strategy->key_char_func(ev);


   switch(ev->keyboard.keycode)
   {
   case ALLEGRO_KEY_S:
      {
         showing_shadow_render = !showing_shadow_render;
      }
      break;
   case ALLEGRO_KEY_1:
      {
         if (!inventory.get_active()) setup_input_mode(INPUT_MODE_PLAYER_CONTROL);
         //input_mode = INPUT_MODE_PLAYER_CONTROL;
      }
      break;
   case ALLEGRO_KEY_2:
      {
         if (!inventory.get_active()) setup_input_mode(INPUT_MODE_WORLD_BUILDING);
         //input_mode = INPUT_MODE_WORLD_BUILDING;
      }
      break;
   case ALLEGRO_KEY_ENTER:
      {
         if (inventory.get_active())
         {
            inventory.hide();
            setup_input_mode(INPUT_MODE_WORLD_BUILDING);
         }
      }
      break;
   case ALLEGRO_KEY_I:
      {
         toggle_inventory();
         if (inventory.get_active()) setup_input_mode(INPUT_MODE_INVENTORY);
         else setup_input_mode(INPUT_MODE_WORLD_BUILDING);
      }
      break;
   case ALLEGRO_KEY_8:
      {
         std::string filename_str = "/Users/markoates/Desktop/screenshot-" + random_string(16) + ".png";
         bool success = false;
         if (shift) success = al_save_bitmap(filename_str.c_str(), al_get_backbuffer(display->al_display));
         if (success) std::cout << "[-] captured screenshot [-]" << std::endl;
         else std::cout << "[!] error capturing screenshot [!]" << std::endl;
      }
      break;
   case ALLEGRO_KEY_SPACE:
      {
         int MICROSECONDS_PER_FRAME = 16670;
         framework->offset_primary_timer(MICROSECONDS_PER_FRAME / 10);
         break;
      }
   case ALLEGRO_KEY_6:
      {
         std::string filename_str = "/Users/markoates/Repos/allegro_flare/bin/data/worlds/world-with-boxes-01.json";
         bool success = false;
         if (shift)
         {
            LevelLoader level_loader(filename_str);
            level_loader.write(&entities, light_target_time_of_day, skybox, camera, casting_light);
            success = true;
            //success = al_save_bitmap(filename_str.c_str(), al_get_backbuffer(display->al_display));
         }
         if (success) std::cout << "[-] saved world to json file [-]" << std::endl;
         else std::cout << "[!] error capturing screenshot [!]" << std::endl;
      }
      break;
   };
}


void FunzDemo::primary_timer_func()
{
   //ALLEGRO_EVENT *this_ev = Framework::current_event;
   if (control_strategy) control_strategy->primary_timer_func();
   update_camera_position_to_target();

   // refresh what entity is currently selected
   update_selected();

   // update the inventory
   inventory.update();

   // update scene entities and states
   update_scene_physics();

   // draw the scene
   draw_scene();

   // draw the hud
   draw_hud();

   //al_flip_display();
}


float FunzDemo::min_zoom = 0.6;
float FunzDemo::max_zoom = 2.0;







//#include <Wicked/SceneRenderer.hpp>


//#ifdef __APPLE__
//#ifndef GL_SILENCE_DEPRECATION
//#define GL_SILENCE_DEPRECATION
//#define ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#endif
//#endif

#include <allegro5/allegro_opengl.h>

//#ifdef __APPLE__
//#ifndef ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#undef GL_SILENCE_DEPRECATION
//#undef ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#endif
//#endif


#include <iostream> // for cout

#include <AllegroFlare/UsefulPHP.hpp>


namespace Wicked
{


SceneRenderer::SceneRenderer()
   : backbuffer_sub_bitmap(nullptr)
   //, depth_shader("data/shaders/depth_vertex.glsl", "data/shaders/depth_fragment.glsl")
   , depth_shader(nullptr)
   , shadow_scale_divisor(1.0) // note, increasing this divisor will
   , initialized(false)
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but reduce
      // the resolution of the shadow. Original engine had a default of 1.0f;

      // Also, this article
      // https://docs.microsoft.com/en-us/windows/win32/dxtecharts/common-techniques-to-improve-shadow-depth-maps
{
}


void SceneRenderer::initialize()
{
   //("data/shaders/depth_vertex.glsl", "data/shaders/depth_fragment.glsl")

   // TODO revise the technique needing a hard-coded path (does not work in test vs produ vs dev environments)
   std::string ROOT_PATH_TO_DATA_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/";


   std::string vertex_filename;
   std::string vertex_file_content;
   std::string fragment_filename;
   std::string fragment_file_content;

   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_vertex.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_fragment.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);

   depth_shader = new AllegroFlare::Shaders::Base("Base", vertex_file_content, fragment_file_content);
   depth_shader->initialize();

   initialized = true;
}


void SceneRenderer::set_shadow_scale_divisor(float shadow_scale_divisor)
{
   this->shadow_scale_divisor = shadow_scale_divisor;
}


void SceneRenderer::set_backbuffer_sub_bitmap(ALLEGRO_BITMAP *backbuffer_sub_bitmap)
{
   this->backbuffer_sub_bitmap = backbuffer_sub_bitmap;
}


void SceneRenderer::refresh_shadow_map(
      std::vector<Entity *> *_entities,
      ShadowCastingLight casting_light,
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface,
      Entity *pointer
   )
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::refresh_shadow_map: ERROR: not initialized");
   if (!_entities) throw std::runtime_error("CCc");
   std::vector<Entity *> &entities = (*_entities);

   // TODO: store and restore states on glEnable/glCullFace, etc
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glIsEnabled.xml
   // ^^ documentation of how this might be approached

   glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   glCullFace(GL_FRONT); 

   //al_set_target_bitmap(backbuffer_sub_bitmap);


   //al_clear_to_color(color::white);
   setup_projection_SHADOW(casting_light, shadow_map_depth_pass_transform);

   // setup the shader
   //depth_shader.use();
   depth_shader->activate();
   
   // draw the objects
   for (unsigned i=0; i<entities.size(); i++)
   {
      entities[i]->draw_for_depth_pass(depth_shader);
   }

   if (pointer)
   {
       pointer->draw_for_depth_pass(depth_shader);
   }


   al_set_target_bitmap(shadow_map_depth_pass_surface); // I *believe* newer versions of allegro have a depth map
                                                        // on a bitmap this may be able to be updated so that the
                                                        // backbuffer does not need be used to render this
   al_draw_bitmap(backbuffer_sub_bitmap, 0, 0, 0);

   //glEnable(GL_CULL_FACE); // requiring opengl should eventually be fazed out
   glCullFace(GL_BACK); 
   //glCullFace(GL_FRONT);
   glDisable(GL_CULL_FACE);
}


void SceneRenderer::setup_projection_SHADOW(
   ShadowCastingLight &shadow_casting_light,
   ALLEGRO_TRANSFORM *transform_to_fill
)
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::setup_projection_SHADOW: ERROR: not initialized");
   if (!backbuffer_sub_bitmap) throw std::runtime_error("AAa");

   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);

   ALLEGRO_TRANSFORM shadow_map_projection;

   shadow_casting_light.reverse_position_transform(&shadow_map_projection);

   ALLEGRO_BITMAP *bitmap = backbuffer_sub_bitmap;
   float divisor = shadow_scale_divisor;
   al_scale_transform_3d(&shadow_map_projection, 150/divisor, 150/divisor, 1); // note, increasing this divisor will
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but
      // reduce the resolution of the shadow. Original engine had a default of 1.0f;

   al_orthographic_transform(
      &shadow_map_projection,
      -al_get_bitmap_width(bitmap),
      al_get_bitmap_height(bitmap),
      30.0,
      al_get_bitmap_width(bitmap),
      -al_get_bitmap_height(bitmap),
      -30.0
   );

   if (transform_to_fill != nullptr)
   {
      al_copy_transform(transform_to_fill, &shadow_map_projection);
   }

   al_use_projection_transform(&shadow_map_projection);
}


void SceneRenderer::setup_projection_SCENE(AllegroFlare::Camera3D &camera, ALLEGRO_TRANSFORM *transform_to_fill)
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::setup_projection_SCENE: ERROR: not initialized");
   camera.setup_projection_on(backbuffer_sub_bitmap);
}


void SceneRenderer::draw_entities(
      vec3d camera_real_position,
      vec3d light_position,
      Entity *skybox,
      std::vector<Entity *> *_entities, 
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface,
      vec2d texture_offset,
      Entity *pointer,
      vec3d camera_looking_at_point
   )
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::draw_entities: ERROR: not initialized");
   if (!skybox)
   {
      static bool skybox_error = false;
      if (!skybox_error)
      {
         //throw std::runtime_error("Xxx");
         std::cout << "SceneRenderer::draw_entities warning! - There is no skybox, the scene will be rendered with a cleared background instead." << std::endl;
         skybox_error = true;
      }
   }
   if (!_entities) throw std::runtime_error("Yyy");
   std::vector<Entity *> &entities = (*_entities);

   //vec3d camera_real_position = camera.get_real_position();
   //vec3d light_position = light.position * 100.0;

   if (skybox)
   {
      // position and draw the skybox
      skybox->place.position = camera_real_position; // note this is not included in "update_scene_physics" because
                                                // it is a rendering-step (skybox will vary depending on camera
                                                // used to render the scene), so not physics-related

      // does this skybox draw need to have a pre-cleared or not-depth checked render?
      skybox->draw(0, 0);
   }
   else
   {
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
   }

   // clear the depth buffer from the skybox
   al_clear_depth_buffer(1);

   for (auto &entity : entities)
   {
      entity->draw(
         camera_real_position,
         light_position,
         shadow_map_depth_pass_transform,
         shadow_map_depth_pass_surface,
         texture_offset
      );
   }

   if (pointer)
   {
      pointer->place.position = camera_looking_at_point; //camera_real_position; // note this is not included in "update_scene_physics" because
      pointer->draw(
         camera_real_position,
         light_position,
         shadow_map_depth_pass_transform,
         shadow_map_depth_pass_surface,
         texture_offset
         );

          //  0, 0);
   }


   //Shader::stop();
   AllegroFlare::Shaders::Base::global_deactivate();
}


void SceneRenderer::draw_scene()
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::draw_scene: ERROR: not initialized");
}


void SceneRenderer::render()
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::render: ERROR: not initialized");
}


} // namespace Wicked








