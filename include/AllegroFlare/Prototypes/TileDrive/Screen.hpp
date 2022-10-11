#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperStepResult.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TerrainMesh.hpp>
#include <AllegroFlare/Prototypes/TileDrive/TileDrive.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <map>
#include <string>
#include <tuple>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace TileDrive
      {
         class Screen : public AllegroFlare::Screens::Base
         {
         private:
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::Prototypes::TileDrive::TileDrive tile_drive;
            bool initialized;

         protected:


         public:
            Screen(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr);
            virtual ~Screen();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            void set_sample_bin(AllegroFlare::SampleBin* sample_bin=nullptr);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
            void set_maps_folder(std::string maps_folder="[unset-maps_folder-arg]");
            void set_terrain_mesh_dictionary(std::map<std::string, std::tuple<std::string, AllegroFlare::Prototypes::TileDrive::TerrainMesh*>> terrain_mesh_dictionary={});
            void set_current_map_identifier(std::string current_map_identifier="[unset-current_map_identifier-arg]");
            void set_collision_stepper_step_result_callback(std::function<void(AllegroFlare::Physics::TileMapCollisionStepperStepResult*,AllegroFlare::Prototypes::TileDrive::TileDrive*,void*)> collision_stepper_step_result_callback={}, void* collision_stepper_step_result_callback_user_data=nullptr);
            void initialize();
            virtual void primary_timer_func() override;
            virtual void key_down_func(ALLEGRO_EVENT* event=nullptr) override;
            virtual void key_up_func(ALLEGRO_EVENT* event=nullptr) override;
         };
      }
   }
}



