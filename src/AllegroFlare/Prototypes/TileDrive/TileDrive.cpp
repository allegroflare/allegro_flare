

#include <AllegroFlare/Prototypes/TileDrive/TileDrive.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshDriverCollisionResolver.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshFactory.hpp>
#include <AllegroFlare/Useful.hpp>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_opengl.h>
#include <cmath>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


TileDrive::TileDrive(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin)
   : event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , current_terrain_mesh(nullptr)
   , terrain_mesh_dictionary({})
   , current_map_identifier("[unset-current_map_identifier]")
   , maps_folder("[unset-maps_folder]")
   , hypersync()
   , driver_position({0, 0, 0})
   , driver_velocity({0, 0, 0})
   , driver_acceleration_velocity(0.0f)
   , driver_turn_rotation(0.0f)
   , driver_turning_velocity(0.0f)
   , driver_accelerator_pressed(false)
   , driver_break_pressed(false)
   , collision_stepper_step_result_callback()
   , collision_stepper_step_result_callback_user_data(nullptr)
   , timer()
   , camera()
   , hud({})
   , state(STATE_WAITING_START)
   , initialized(false)
   , debug_metronome_sound(nullptr)
   , music_started_at(0.0f)
{
}


TileDrive::~TileDrive()
{
}


void TileDrive::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void TileDrive::set_collision_stepper_step_result_callback(std::function< void( AllegroFlare::Physics::TileMapCollisionStepperStepResult*, AllegroFlare::Prototypes::TileDrive::TileDrive*, void* ) > collision_stepper_step_result_callback)
{
   this->collision_stepper_step_result_callback = collision_stepper_step_result_callback;
}


void TileDrive::set_collision_stepper_step_result_callback_user_data(void* collision_stepper_step_result_callback_user_data)
{
   this->collision_stepper_step_result_callback_user_data = collision_stepper_step_result_callback_user_data;
}


AllegroFlare::EventEmitter* TileDrive::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* TileDrive::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* TileDrive::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::SampleBin* TileDrive::get_sample_bin() const
{
   return sample_bin;
}


std::string TileDrive::get_current_map_identifier() const
{
   return current_map_identifier;
}


std::string TileDrive::get_maps_folder() const
{
   return maps_folder;
}


std::function< void( AllegroFlare::Physics::TileMapCollisionStepperStepResult*, AllegroFlare::Prototypes::TileDrive::TileDrive*, void* ) > TileDrive::get_collision_stepper_step_result_callback() const
{
   return collision_stepper_step_result_callback;
}


void* TileDrive::get_collision_stepper_step_result_callback_user_data() const
{
   return collision_stepper_step_result_callback_user_data;
}


AllegroFlare::Prototypes::TileDrive::TerrainMesh* &TileDrive::get_current_terrain_mesh_ref()
{
   return current_terrain_mesh;
}


std::map<std::string, std::tuple<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMesh*>> &TileDrive::get_terrain_mesh_dictionary_ref()
{
   return terrain_mesh_dictionary;
}


void TileDrive::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void TileDrive::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_sample_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->sample_bin = sample_bin;
   return;
}

void TileDrive::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->font_bin = font_bin;
   return;
}

void TileDrive::set_maps_folder(std::string maps_folder)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_maps_folder" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->maps_folder = maps_folder;
   return;
}

void TileDrive::set_terrain_mesh_dictionary(std::map<std::string, std::tuple<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMesh*>> terrain_mesh_dictionary)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_terrain_mesh_dictionary" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->terrain_mesh_dictionary = terrain_mesh_dictionary;
   return;
}

void TileDrive::set_current_map_identifier(std::string current_map_identifier)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "set_current_map_identifier" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->current_map_identifier = current_map_identifier;
   return;
}

void TileDrive::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"al_is_acodec_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "initialize" << ": error: " << "guard \"sample_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory factory(bitmap_bin);
   //current_terrain_mesh = factory.create_classic_random();
   //current_terrain_mesh = factory.create_random_with_walls();
   //std::string map_filename = "/Users/markoates/Repos/allegro_flare/bin/data/maps/tunnel_mesh-02.tmj";
   //current_terrain_mesh = factory.create_from_tmj(map_filename);



   //std::map<std::string std::pair<std::string, 

   //std::string maps_folder = "/Users/markoates/Repos/allegro_flare/bin/data/maps/";
   // load all the maps
   //terrain_mesh_dictionary = {
      //{ "og-tunnel-mesh", { "tunnel_mesh-02.tmj", nullptr } },
   //};
   //current_terrain_mesh = factory.create_from_tmj(map_filename);
   //= factory.create_from_tmj(map_filename);


   // load up all the maps
   for (auto& terrain_mesh_dictionary_item : terrain_mesh_dictionary)
   {
      std::string identifier = terrain_mesh_dictionary_item.first;
      std::string filename = std::get<0>(terrain_mesh_dictionary_item.second);
      AllegroFlare::Prototypes::TileDrive::TerrainMesh* &mesh_ptr = std::get<1>(terrain_mesh_dictionary_item.second);

      mesh_ptr = factory.create_from_tmj(maps_folder + filename);
      if (!mesh_ptr)
      {
         std::stringstream error_message;
         error_message << "AllegroFlare::Prototypes::TileDrive::TileDrive::initialize error: "
                       << "could not load file \""
                       << filename << "\" for identifier \"" << identifier << "\"";
         throw std::runtime_error(error_message.str());
      }
   }



   //std::string map_filename = "/Users/markoates/Repos/allegro_flare/bin/data/maps/tunnel_mesh-02.tmj";
   //current_terrain_mesh = factory.create_from_tmj(map_filename);
   //std::string current_map_identifier = "og-tunnel-mesh";
   bool map_of_identifier_exists = (terrain_mesh_dictionary.count(current_map_identifier) == 1);
   if (!map_of_identifier_exists)
   {
      // TODO: move this code to an external function
      // TODO: enable loading arbitrary maps by identifier from the dictionary
      std::stringstream error_message;
      error_message << "AllegroFlare::Prototypes::TileDrive::TileDrive::initialize error: "
                    << "there is not a map that has the name \"" << current_map_identifier << "\". Could not load.";
      throw std::runtime_error(error_message.str());
   }
   current_terrain_mesh = std::get<1>(terrain_mesh_dictionary[current_map_identifier]);


   // create local music track playlist
   std::map<std::string, std::pair<std::string, float>> playlist = {
      { "song-60bpm",     { "music_tracks/tempo-track-60.ogg", 60.0f } },
      { "song-80bpm",     { "music_tracks/tempo-track-80.ogg", 80.0f } },
      { "song-120bpm",     { "music_tracks/tempo-track-120.ogg", 120.0f } },
      { "song-152bpm",     { "music_tracks/tempo-track-152.ogg", 152.0f } },
      { "original-jamzz",  { "music_tracks/some-jamzz-04.ogg", 130.0f } },
   };

   //std::string playlist_song_to_play = "song-152bpm";
   //std::string playlist_song_to_play = "song-80bpm";
   //std::string playlist_song_to_play = "song-120bpm";
   std::string playlist_song_to_play = "original-jamzz";

   std::string pwd = "/Users/markoates/Repos/allegro_flare/bin/data/samples/";
   std::string song_filename = pwd + playlist[playlist_song_to_play].first;
   float song_bpm = playlist[playlist_song_to_play].second;

   hypersync.set_song_filename(song_filename);
   hypersync.set_song_bpm(song_bpm);
   hypersync.initialize();


   debug_metronome_sound = new AllegroFlare::Sound(sample_bin->auto_get("metronome-01.ogg"));

   hud.set_font_bin(font_bin);
   hud.set_timer(&timer);
   hud.initialize();

   initialized = true;
   return;
}

void TileDrive::start_timer()
{
   timer.start();
   return;
}

void TileDrive::pause_timer()
{
   timer.pause();
   return;
}

void TileDrive::reset_timer()
{
   timer.reset();
   return;
}

float TileDrive::calculate_current_terrain_mesh_height()
{
   if (!current_terrain_mesh) return 0.0f;
   return current_terrain_mesh->infer_real_height();
}

float TileDrive::calculate_current_terrain_mesh_tile_depth()
{
   if (!current_terrain_mesh) return 0.0f;
   return current_terrain_mesh->obtain_tile_height();
}

void TileDrive::reset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "reset" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   driver_position.x = current_terrain_mesh->infer_real_width() * 0.5
                     - current_terrain_mesh->obtain_tile_width() * 0.5;
   driver_position.z = current_terrain_mesh->infer_real_height()
                     - current_terrain_mesh->obtain_tile_height();

   driver_velocity = AllegroFlare::Vec3D(0, 0, 0);

   camera.stepout = AllegroFlare::Vec3D(0, 2, 5);
   state = STATE_WAITING_START;

   hud.show_ready_slate();
   //camera.tilt = 0.4;
   //camera.zoom = 2.1;
   //camera.spin += 0.01f;
   music_started_at = 0.0f;

   // TODO: hypersync->stop();
   reset_timer();
   return;
}

void TileDrive::start()
{
   if (state != STATE_WAITING_START) return;
   state = STATE_RACING;

   hypersync.start();

   start_timer();
   hud.clear_slate();
   return;
}

void TileDrive::driver_turn_right()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_turning_velocity = 0.02;
   return;
}

void TileDrive::driver_turn_left()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_turning_velocity = -0.02;
   return;
}

void TileDrive::driver_strafe_right()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_velocity.x = 3;
   return;
}

void TileDrive::driver_strafe_left()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_velocity.x = -3;
   return;
}

void TileDrive::driver_press_accelerator()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_accelerator_pressed = true;
   //driver_velocity.z = -20;
   return;
}

void TileDrive::driver_unpress_accelerator()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_accelerator_pressed = false;
   return;
}

void TileDrive::driver_press_break()
{
   if (state != STATE_RACING) return;
   driver_break_pressed = true;
   return;
}

void TileDrive::driver_unpress_break()
{
   if (state != STATE_RACING) return;
   driver_break_pressed = false;
   return;
}

void TileDrive::driver_stop()
{
   if (state == STATE_WAITING_START) start();
   if (state != STATE_RACING) return;
   driver_velocity.z = 0;
   return;
}

void TileDrive::driver_strafe_none()
{
   driver_velocity.x = 0;
   return;
}

void TileDrive::driver_turn_none()
{
   driver_turning_velocity = 0;
   return;
}

void TileDrive::render_terrain()
{
   current_terrain_mesh->render();
   return;
}

void TileDrive::render_hud()
{
   hud.render();
   return;
}

void TileDrive::render_driver()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "render_driver" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   draw_crosshair(driver_position, AllegroFlare::Color::Yellow, 0.75);
   return;
}

void TileDrive::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }

   //driver_turn_rotation += driver_turning_velocity;
   //float &angle = driver_turn_rotation;
   //float &magnitude = driver_acceleration_velocity;
   //driver_velocity = AllegroFlare::Vec3D(magnitude * std::cos(angle), 0, magnitude * std::sin(angle));

   if (driver_break_pressed)
   {
      float driver_break_velocity = 0.3;
      float DRIVER_MAX_REVERSE_VELOCITY = 4;

      driver_acceleration_velocity += driver_break_velocity;
      if (driver_acceleration_velocity >= DRIVER_MAX_REVERSE_VELOCITY)
      {
         driver_acceleration_velocity = DRIVER_MAX_REVERSE_VELOCITY;
      }
      //driver_velocity.z += driver_break_velocity;
      //if (driver_velocity.z >= DRIVER_MAX_REVERSE_VELOCITY) driver_velocity.z = DRIVER_MAX_REVERSE_VELOCITY;
   }
   else if (driver_accelerator_pressed)
   {
      float driver_accelerator_velocity = -0.2;
      float DRIVER_MAX_FORWARD_VELOCITY = -6;

      driver_acceleration_velocity += driver_accelerator_velocity;
      if (driver_acceleration_velocity <= DRIVER_MAX_FORWARD_VELOCITY)
      {
         driver_acceleration_velocity = DRIVER_MAX_FORWARD_VELOCITY;
      }
      //driver_velocity.z += driver_accelerator_velocity;
      //if (driver_velocity.z <= DRIVER_MAX_FORWARD_VELOCITY) driver_velocity.z = DRIVER_MAX_FORWARD_VELOCITY;
   }



   driver_turn_rotation += driver_turning_velocity;
   float &angle = driver_turn_rotation;
   float &magnitude = driver_acceleration_velocity;
   float angle_offset = 3.14 / 2;
   driver_velocity = AllegroFlare::Vec3D(
      magnitude * std::cos(angle+angle_offset),
      0,
      magnitude * std::sin(angle+angle_offset)
   );
   //driver_velocity.


   // NOTE: do not include natural decelaration or environmental friction for this racer

   // handle collision resolving including collisions that will stop the player

   AllegroFlare::Prototypes::TileDrive::TerrainMeshDriverCollisionResolver collision_resolver(
      current_terrain_mesh,
      &driver_position,
      &driver_velocity
   );
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result = collision_resolver.resolve();
   // call the callback after the stepper has processed the step
   if (collision_stepper_step_result_callback)
   {
      collision_stepper_step_result_callback(
         &step_result,
         this,
         collision_stepper_step_result_callback_user_data
      );
   }

   camera.position = driver_position;
   camera.spin = driver_turn_rotation;

   return;
}

void TileDrive::development_play_around_with_collision_steper_callback(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result, AllegroFlare::Prototypes::TileDrive::TileDrive* tile_drive, void* user_data)
{
   if (!(step_result))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "development_play_around_with_collision_steper_callback" << ": error: " << "guard \"step_result\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(tile_drive))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "development_play_around_with_collision_steper_callback" << ": error: " << "guard \"tile_drive\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (step_result->get_collisions_ref().empty()) return;

   AllegroFlare::Prototypes::TileDrive::TerrainMesh *current_terrain_mesh =
      tile_drive->get_current_terrain_mesh_ref();
   if (!current_terrain_mesh) return;

   //event_emitter->emit_play_sound_effect_event("menu-click-01.ogg");
   //debug_metronome_sound->stop();
   //debug_metronome_sound->play();

   for (auto &collision : step_result->get_collisions_ref())
   {
      if (collision.get_tile_value() == 0)
      {
         //stop_racing_due_to_death();
      }

      // change tiles if driver collided with them
      else if (collision.get_tile_value() == 2 || (collision.get_tile_value() == -999))
      {
         // this is cool just disabled
         bool disable_this_feature = false;
         if (!disable_this_feature)
         {
            AllegroFlare::Physics::Int2D tile_pos = collision.get_collided_tile_coordinate();
            current_terrain_mesh->get_prim_mesh_ref().set_tile_id(tile_pos.get_x(), tile_pos.get_y(), 3);
            //current_terrain_mesh->get_collision_tile_map_ref().set_tile(tile_pos.get_x(), tile_pos.get_y(), 0);
         }
      }
   }
   return;
}

void TileDrive::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TileDrive" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   //al_clear_depth_buffer(1);
   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));

   //glCullFace(GL_BACK);  // requiring opengl should evnetually be fazed out
   //glDisable(GL_CULL_FACE);

   //camera.start_reverse_transform();
   //AllegroFlare::Placement3D place;
   //place.start_transform();
   render_terrain();
   render_driver();
   //place.restore_transform();
   //camera.restore_transform();

   render_hud();
   return;
}


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


