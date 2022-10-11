#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>
#include <AllegroFlare/Prototypes/TileDrive/Hud/Hud.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/Timer.hpp>
#include <AllegroFlare/Vec3D.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class TileDrive
         {
         public:
            static constexpr int STATE_RACING = 1;
            static constexpr int STATE_WON = 2;
            static constexpr int STATE_PLAYER_DIED = 3;
            static constexpr int STATE_WAITING_START = 4;

         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* current_terrain_mesh;
            AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
            AllegroFlare::Vec3D surfer_position;
            AllegroFlare::Vec3D surfer_velocity;
            bool surfer_accelerator_pressed;
            bool surfer_break_pressed;
            AllegroFlare::Timer timer;
            AllegroFlare::Camera3D camera;
            AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
            int state;
            bool surfer_attached_to_playhead_track;
            bool initialized;
            AllegroFlare::Sound* debug_metronome_sound;
            float music_started_at;
            void start_timer();
            void reset_timer();
            float calculate_current_terrain_mesh_height();
            float calculate_current_terrain_mesh_tile_depth();
            void evaluate_surfer_past_goal();

         protected:


         public:
            TileDrive(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr);
            ~TileDrive();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::SampleBin* get_sample_bin() const;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* &get_current_terrain_mesh_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void pause_timer();
            void reset();
            void start_racing();
            void attach_surfer_to_playhead_track();
            void stop_racing_due_to_death();
            void surfer_move_right();
            void surfer_move_left();
            void surfer_press_accelerator();
            void surfer_unpress_accelerator();
            void surfer_press_break();
            void surfer_unpress_break();
            void surfer_stop();
            void surfer_move_horizontal_none();
            void render_terrain();
            void render_hud();
            void render_surfer();
            void update();
            void play_around_with_collision_step_result(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result=nullptr);
            void render();
         };
      }
   }
}



