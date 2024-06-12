

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMeshSurferCollisionResolver.hpp>
#include <AllegroFlare/Useful.hpp>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_opengl.h>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


MindDive::MindDive(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin)
   : event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , current_tunnel_mesh()
   , hypersync()
   , surfer_position({0, 0, 0})
   , surfer_velocity({0, 0, 0})
   , surfer_accelerator_pressed(false)
   , surfer_break_pressed(false)
   , timer()
   , camera()
   , hud({})
   , state(STATE_WAITING_START)
   , surfer_attached_to_playhead_track(false)
   , initialized(false)
   , debug_metronome_sound(nullptr)
   , music_started_at(0.0f)
{
}


MindDive::~MindDive()
{
}


void MindDive::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


AllegroFlare::EventEmitter* MindDive::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* MindDive::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* MindDive::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::SampleBin* MindDive::get_sample_bin() const
{
   return sample_bin;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh* &MindDive::get_current_tunnel_mesh_ref()
{
   return current_tunnel_mesh;
}


void MindDive::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void MindDive::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::set_sample_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::set_sample_bin]: error: guard \"(!initialized)\" not met");
   }
   this->sample_bin = sample_bin;
   return;
}

void MindDive::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void MindDive::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"al_is_audio_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"al_is_audio_installed()\" not met");
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"al_is_acodec_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"al_is_acodec_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"sample_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::initialize]: error: guard \"sample_bin\" not met");
   }
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory factory(bitmap_bin);
   //current_tunnel_mesh = factory.create_classic_random();
   //current_tunnel_mesh = factory.create_random_with_walls();
   std::string map_filename = "/Users/markoates/Repos/allegro_flare/bin/data/maps/tunnel_mesh-02.tmj";
   current_tunnel_mesh = factory.create_from_tmj(map_filename);

   // TODO: abstract this so it can be tested with a test data ogg file.
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

void MindDive::start_timer()
{
   timer.start();
   return;
}

void MindDive::pause_timer()
{
   timer.pause();
   return;
}

void MindDive::reset_timer()
{
   timer.reset();
   return;
}

float MindDive::calculate_current_tunnel_mesh_height()
{
   if (!current_tunnel_mesh) return 0.0f;
   return current_tunnel_mesh->infer_real_height();
}

float MindDive::calculate_current_tunnel_mesh_tile_depth()
{
   if (!current_tunnel_mesh) return 0.0f;
   return current_tunnel_mesh->obtain_tile_height();
}

void MindDive::reset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::reset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::reset]: error: guard \"initialized\" not met");
   }
   surfer_position.x = current_tunnel_mesh->infer_real_width() * 0.5
                     - current_tunnel_mesh->obtain_tile_width() * 0.5;
   surfer_position.z = current_tunnel_mesh->infer_real_height()
                     - current_tunnel_mesh->obtain_tile_height();

   surfer_velocity = AllegroFlare::Vec3D(0, 0, 0);

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

void MindDive::start_racing()
{
   if (state != STATE_WAITING_START) return;
   state = STATE_RACING;

   attach_surfer_to_playhead_track();
   hypersync.start();

   start_timer();
   hud.clear_slate();
   return;
}

void MindDive::attach_surfer_to_playhead_track()
{
   surfer_attached_to_playhead_track = true;
   return;
}

void MindDive::stop_racing_due_to_death()
{
   if (state == STATE_PLAYER_DIED) return;
   state = STATE_PLAYER_DIED;
   pause_timer();
   surfer_velocity.x = 0.0f;
   surfer_velocity.z = 0.0f;
   hud.show_die_slate();
   return;
}

void MindDive::surfer_move_right()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_velocity.x = 3;
   return;
}

void MindDive::surfer_move_left()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_velocity.x = -3;
   return;
}

void MindDive::surfer_press_accelerator()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_accelerator_pressed = true;
   //surfer_velocity.z = -20;
   return;
}

void MindDive::surfer_unpress_accelerator()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_accelerator_pressed = false;
   return;
}

void MindDive::surfer_press_break()
{
   if (state != STATE_RACING) return;
   surfer_break_pressed = true;
   return;
}

void MindDive::surfer_unpress_break()
{
   if (state != STATE_RACING) return;
   surfer_break_pressed = false;
   return;
}

void MindDive::surfer_stop()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_velocity.z = 0;
   return;
}

void MindDive::surfer_move_horizontal_none()
{
   surfer_velocity.x = 0;
   return;
}

void MindDive::render_tunnel()
{
   current_tunnel_mesh->render();
   return;
}

void MindDive::render_hud()
{
   hud.render();
   return;
}

void MindDive::render_surfer()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::render_surfer]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::render_surfer]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   draw_crosshair(surfer_position, AllegroFlare::Color::Yellow, 0.75);
   return;
}

void MindDive::evaluate_surfer_past_goal()
{
   if (state != STATE_RACING) return;

   if (surfer_position.z <= 0)
   {
      timer.pause();
      state = STATE_WON;
      surfer_velocity.x = 0.0f;
      surfer_velocity.z = 0.0f;
      hud.show_win_slate();
   }

   return;
}

void MindDive::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::update]: error: guard \"initialized\" not met");
   }
   if (surfer_attached_to_playhead_track) // the player velocity is synchronized to the music track
   {
      // TODO: set thes velocity relative to the music
      surfer_velocity.z = -6.0;

      AllegroFlare::Prototypes::MindDive::TunnelMeshSurferCollisionResolver collision_resolver(
         current_tunnel_mesh,
         &surfer_position,
         &surfer_velocity
      );
      AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result = collision_resolver.resolve_basic();
      play_around_with_collision_step_result(&step_result);
   }
   else // player controls speed and velocity of surfer
   {
      if (surfer_break_pressed)
      {
         float surfer_break_velocity = 0.2;
         float SURFER_MAX_REVERSE_VELOCITY = 4;

         surfer_velocity.z += surfer_break_velocity;
         if (surfer_velocity.z >= SURFER_MAX_REVERSE_VELOCITY) surfer_velocity.z = SURFER_MAX_REVERSE_VELOCITY;
      }
      else if (surfer_accelerator_pressed)
      {
         float surfer_accelerator_velocity = -0.1;
         float SURFER_MAX_FORWARD_VELOCITY = -20;

         surfer_velocity.z += surfer_accelerator_velocity;
         if (surfer_velocity.z <= SURFER_MAX_FORWARD_VELOCITY) surfer_velocity.z = SURFER_MAX_FORWARD_VELOCITY;
      }

      // NOTE: do not include natural decelaration or environmental friction for this racer

      // handle collision resolving including collisions that will stop the player

      AllegroFlare::Prototypes::MindDive::TunnelMeshSurferCollisionResolver collision_resolver(
         current_tunnel_mesh,
         &surfer_position,
         &surfer_velocity
      );
      AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result = collision_resolver.resolve();
      play_around_with_collision_step_result(&step_result);
   }

   camera.position = surfer_position;

   evaluate_surfer_past_goal();

   return;
}

void MindDive::play_around_with_collision_step_result(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result)
{
   if (!(step_result))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::play_around_with_collision_step_result]: error: guard \"step_result\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::play_around_with_collision_step_result]: error: guard \"step_result\" not met");
   }
   if (!(current_tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::play_around_with_collision_step_result]: error: guard \"current_tunnel_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::play_around_with_collision_step_result]: error: guard \"current_tunnel_mesh\" not met");
   }
   if (step_result->get_collisions_ref().empty()) return;

   //event_emitter->emit_play_sound_effect_event("menu-click-01.ogg");
   //debug_metronome_sound->stop();
   //debug_metronome_sound->play();

   for (auto &collision : step_result->get_collisions_ref())
   {
      // stop racing due do death
      if (collision.get_tile_value() == 0)
      {
         stop_racing_due_to_death();
      }

      // change tiles if surfer collided with them
      else if (collision.get_tile_value() == 2 || (collision.get_tile_value() == -999))
      {
         // this is cool just disabled
         bool disable_this_feature = false;
         if (!disable_this_feature)
         {
            AllegroFlare::Physics::Int2D tile_pos = collision.get_collided_tile_coordinate();
            current_tunnel_mesh->get_prim_mesh_ref().set_tile_id(tile_pos.get_x(), tile_pos.get_y(), 3);
            //current_tunnel_mesh->get_collision_tile_map_ref().set_tile(tile_pos.get_x(), tile_pos.get_y(), 0);
         }
      }
   }
   return;
}

void MindDive::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::MindDive::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::MindDive::render]: error: guard \"initialized\" not met");
   }
   //al_clear_depth_buffer(1);
   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));

   //glCullFace(GL_BACK);  // requiring opengl should evnetually be fazed out
   //glDisable(GL_CULL_FACE);

   //camera.start_reverse_transform();
   //AllegroFlare::Placement3D place;
   //place.start_transform();
   render_tunnel();
   render_surfer();
   //place.restore_transform();
   //camera.restore_transform();

   render_hud();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


