#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/MindDive/Hud/Hud.hpp>
#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMesh.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/Timer.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace MindDive
      {
         class MindDive
         {
         public:
            static constexpr int STATE_RACING = 1;
            static constexpr int STATE_WON = 2;
            static constexpr int STATE_DEAD = 3;
            static constexpr int STATE_WAITING_START = 4;

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* current_tunnel_mesh;
            AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
            AllegroFlare::Sound* current_music_track;
            float current_music_track_bpm;
            AllegroFlare::Vec3D surfer_position;
            AllegroFlare::Vec3D surfer_velocity;
            AllegroFlare::Timer timer;
            AllegroFlare::Camera3D camera;
            AllegroFlare::Prototypes::MindDive::Hud::Hud hud;
            int state;
            bool surfer_attached_to_playhead;
            bool initialized;
            AllegroFlare::Sound* debug_metronome_sound;
            float music_started_at;
            void start_timer();
            void reset_timer();
            float calculate_current_tunnel_mesh_height();
            float calculate_current_tunnel_mesh_tile_depth();
            void evaluate_surfer_past_goal();

         protected:


         public:
            MindDive(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr);
            ~MindDive();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::SampleBin* get_sample_bin() const;
            AllegroFlare::Prototypes::MindDive::TunnelMesh* &get_current_tunnel_mesh_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void pause_timer();
            void reset();
            void start_racing();
            void attach_surfer_to_playhead();
            void stop_racing_due_to_death();
            void surfer_move_right();
            void surfer_move_left();
            void surfer_accelerate();
            void surfer_reverse();
            void surfer_stop();
            void surfer_move_horizontal_none();
            void render_tunnel();
            void render_hud();
            void render_surfer();
            void update();
            void play_around_with_collision_step_result(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result=nullptr);
            void render();
         };
      }
   }
}



