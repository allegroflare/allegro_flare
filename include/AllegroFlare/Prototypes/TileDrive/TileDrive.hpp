#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Elements/Backgrounds/Parallax.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/TileDrive/Hud/Hud.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshDictionaryRecord.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TileDrive.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Sound.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <functional>
#include <map>
#include <string>


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
            std::map<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord> terrain_mesh_dictionary;
            std::string current_map_identifier;
            std::string maps_folder;
            AllegroFlare::Vec3D driver_position;
            AllegroFlare::Vec3D driver_velocity;
            float driver_acceleration_velocity;
            float driver_turn_rotation;
            float driver_turning_velocity;
            bool driver_accelerator_pressed;
            bool driver_break_pressed;
            std::function< void( AllegroFlare::Physics::TileMapCollisionStepperStepResult*, AllegroFlare::Prototypes::TileDrive::TileDrive*, void* ) > collision_stepper_step_result_callback;
            void* collision_stepper_step_result_callback_user_data;
            AllegroFlare::Elements::Backgrounds::Parallax parallax_background;
            AllegroFlare::Camera3D camera;
            AllegroFlare::Prototypes::TileDrive::Hud::Hud hud;
            int state;
            bool initialized;
            AllegroFlare::Sound* debug_metronome_sound;
            float calculate_current_terrain_mesh_height();
            float calculate_current_terrain_mesh_tile_depth();

         protected:


         public:
            TileDrive(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr);
            ~TileDrive();

            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_collision_stepper_step_result_callback(std::function< void( AllegroFlare::Physics::TileMapCollisionStepperStepResult*, AllegroFlare::Prototypes::TileDrive::TileDrive*, void* ) > collision_stepper_step_result_callback);
            void set_collision_stepper_step_result_callback_user_data(void* collision_stepper_step_result_callback_user_data);
            AllegroFlare::EventEmitter* get_event_emitter() const;
            AllegroFlare::BitmapBin* get_bitmap_bin() const;
            AllegroFlare::FontBin* get_font_bin() const;
            AllegroFlare::SampleBin* get_sample_bin() const;
            std::string get_current_map_identifier() const;
            std::string get_maps_folder() const;
            std::function< void( AllegroFlare::Physics::TileMapCollisionStepperStepResult*, AllegroFlare::Prototypes::TileDrive::TileDrive*, void* ) > get_collision_stepper_step_result_callback() const;
            void* get_collision_stepper_step_result_callback_user_data() const;
            AllegroFlare::Prototypes::TileDrive::TerrainMesh* &get_current_terrain_mesh_ref();
            std::map<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord> &get_terrain_mesh_dictionary_ref();
            AllegroFlare::Elements::Backgrounds::Parallax &get_parallax_background_ref();
            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_maps_folder(std::string maps_folder="[unset-maps_folder-arg]");
            void set_terrain_mesh_dictionary(std::map<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord> terrain_mesh_dictionary={});
            void set_current_map_identifier(std::string current_map_identifier="[unset-current_map_identifier-arg]");
            void initialize();
            void reset();
            void start();
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
            static void development_play_around_with_collision_steper_callback(AllegroFlare::Physics::TileMapCollisionStepperStepResult* step_result=nullptr, AllegroFlare::Prototypes::TileDrive::TileDrive* tile_drive=nullptr, void* user_data=nullptr);
            void render_background();
            void render_world();
            void render();
         };
      }
   }
}



