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
            AllegroFlare::Vec3D driver_position;
            AllegroFlare::Vec3D driver_velocity;
            float driver_turn_rotation;
            bool driver_accelerator_pressed;
            bool driver_break_pressed;
            AllegroFlare::Timer timer;
            AllegroFlare::Camera3D camera;
            AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
            int state;
            bool initialized;
            AllegroFlare::Sound* debug_metronome_sound;
            float music_started_at;
            void start_timer();
            void reset_timer();
            float calculate_current_terrain_mesh_height();
            float calculate_current_terrain_mesh_tile_depth();
            void evaluate_driver_past_goal();

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
            void stop_racing_due_to_death();
            void driver_turn_right();
            void driver_turn_left();
            void driver_strafe_right();
            void driver_strafe_left();
            void driver_press_accelerator();
            void driver_unpress_accelerator();
            void driver_press_break();
            void driver_unpress_break();
            void driver_stop();
            void driver_strafe_none();
            void driver_turn_none();
            void render_terrain();
            void render_hud();
            void render_driver();
            void update();
            void play_around_with_collision_step_result(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result=nullptr);
            void render();
         };
      }
   }
}



