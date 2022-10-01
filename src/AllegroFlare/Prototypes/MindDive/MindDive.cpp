

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
   , current_music_track(nullptr)
   , current_music_track_bpm(130.0f)
   , surfer_position({0, 0, 0})
   , surfer_velocity({0, 0, 0})
   , timer()
   , camera()
   , hud({})
   , state(STATE_WAITING_START)
   , surfer_attached_to_playhead(false)
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
      error_message << "MindDive" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void MindDive::set_sample_bin(AllegroFlare::SampleBin* sample_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "set_sample_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->sample_bin = sample_bin;
   return;
}

void MindDive::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->font_bin = font_bin;
   return;
}

float MindDive::infer_playhead_position_sec()
{
   if (!current_music_track) return 0;
   return current_music_track->position();
}

void MindDive::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_audio_installed()))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"al_is_audio_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_acodec_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"al_is_acodec_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"event_emitter\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"sample_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory factory(bitmap_bin);
   //current_tunnel_mesh = factory.create_classic_random();
   current_tunnel_mesh = factory.create_random_with_walls();

   //current_music_track_identifier = "music_tracks/some-jamzz-04.ogg";
   std::string current_music_track_identifier = "music_tracks/tempo-track-152.ogg";
   //current_music_track_bpm = 152;
   current_music_track_bpm = 152;
   current_music_track = new AllegroFlare::Sound(sample_bin->auto_get(current_music_track_identifier));

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
      error_message << "MindDive" << "::" << "reset" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   surfer_position.x = current_tunnel_mesh->infer_real_width() * 0.5
                     - current_tunnel_mesh->obtain_tile_width() * 0.5;
   surfer_position.z = current_tunnel_mesh->infer_real_height()
                     - current_tunnel_mesh->obtain_tile_height() * 0.5;

   surfer_velocity = AllegroFlare::Vec3D(0, 0, 0);

   camera.stepout = AllegroFlare::Vec3D(0, 2, 5);
   state = STATE_WAITING_START;

   hud.show_ready_slate();
   //camera.tilt = 0.4;
   //camera.zoom = 2.1;
   //camera.spin += 0.01f;
   music_started_at = 0.0f;

   //event_emitter->emit_play_music_track_event("[unset-music-track-identifier]");
   if (current_music_track) current_music_track->stop();
   reset_timer();
   return;
}

void MindDive::start_racing()
{
   if (state != STATE_WAITING_START) return;
   state = STATE_RACING;
   if (current_music_track)
   {
      attach_surfer_to_playhead();
      current_music_track->play();
      current_music_track->volume(0.01);
      music_started_at = al_get_time();
   }
   start_timer();
   hud.clear_slate();
   return;
}

void MindDive::attach_surfer_to_playhead()
{
   surfer_attached_to_playhead = true;
   return;
}

void MindDive::stop_racing_due_to_death()
{
   if (state == STATE_DEAD) return;
   state = STATE_DEAD;
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

void MindDive::surfer_accelerate()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_velocity.z = -20;
   return;
}

void MindDive::surfer_reverse()
{
   if (state == STATE_WAITING_START) start_racing();
   if (state != STATE_RACING) return;
   surfer_velocity.z = 2;
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
      error_message << "MindDive" << "::" << "render_surfer" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   draw_crosshair(surfer_position, AllegroFlare::Color::Yellow, 0.75);
   //al_draw_filled_circle(surfer_position.x, surfer_position.z, 0.25, ALLEGRO_COLOR{1, 1, 1, 1});
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
      error_message << "MindDive" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (surfer_attached_to_playhead)
   {
      float explicit_playhead_position = al_get_time() - music_started_at;

      // update the surfer playhead position
      //float song_bpm = current_music_track_bpm;
      float song_bpm = 130.0;
      static const float SECONDS_PER_MINUTE = 60.0f;
      static const int TILES_PER_BEAT = 4;
      //float time_multiplier = SECONDS_PER_MINUTE / song_bpm;
      float time_multiplier = song_bpm / SECONDS_PER_MINUTE;
      float playhead_tile_position = calculate_current_tunnel_mesh_tile_depth() * TILES_PER_BEAT
                                   * explicit_playhead_position
                                   * time_multiplier;
                                   
                                   //* infer_playhead_position_sec();
                                   //* time_multiplier;

      surfer_position.z = calculate_current_tunnel_mesh_height() - playhead_tile_position;
      surfer_velocity.z = -1.0f * TILES_PER_BEAT;
                               // this is implicit, and only used for the collision resolver to calculate
                               // collisions.  It should be set constant to the rate of the music track playing
   }

   AllegroFlare::Prototypes::MindDive::TunnelMeshSurferCollisionResolver collision_resolver(
      current_tunnel_mesh,
      &surfer_position,
      &surfer_velocity
   );
   AllegroFlare::Physics::TileMapCollisionStepperStepResult step_result = collision_resolver.resolve();

   play_around_with_collision_step_result(&step_result);

   camera.position = surfer_position;

   evaluate_surfer_past_goal();

   return;
}

void MindDive::play_around_with_collision_step_result(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result)
{
   if (!(step_result))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "play_around_with_collision_step_result" << ": error: " << "guard \"step_result\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(current_tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "play_around_with_collision_step_result" << ": error: " << "guard \"current_tunnel_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (step_result->get_collisions_ref().empty()) return;

   //event_emitter->emit_play_sound_effect_event("menu-click-01.ogg");
   debug_metronome_sound->stop();
   debug_metronome_sound->play();

   for (auto &collision : step_result->get_collisions_ref())
   {
      // stop racing due do death
      if (collision.get_tile_value() == 0)
      {
         stop_racing_due_to_death();
      }

      // change tiles if surfer collided with them
      else if (collision.get_tile_value() == 2)
      {
         // this is cool just disabled
         bool disable_this_feature = true;
         if (!disable_this_feature)
         {
            AllegroFlare::Physics::Int2D tile_pos = collision.get_collided_tile_coordinate();
            current_tunnel_mesh->get_prim_mesh_ref().set_tile_id(tile_pos.get_x(), tile_pos.get_y(), 3);
            current_tunnel_mesh->get_collision_tile_map_ref().set_tile(tile_pos.get_x(), tile_pos.get_y(), 0);
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
      error_message << "MindDive" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
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


