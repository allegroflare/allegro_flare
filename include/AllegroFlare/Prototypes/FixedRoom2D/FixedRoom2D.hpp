#pragma once


#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/InteractionEventData.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <map>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class FixedRoom2D
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::AudioController* audio_controller;
            AllegroFlare::Inventory af_inventory;
            AllegroFlare::Elements::Inventory inventory_window;
            AllegroFlare::Inventory flags;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> script_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_runner;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Room room;
            bool initialized;

         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::AudioController* audio_controller=nullptr);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_audio_controller(AllegroFlare::AudioController* audio_controller);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            void initialize();
            void update();
            void render();
            void process_interaction_event(AllegroFlare::Prototypes::FixedRoom2D::InteractionEventData* interaction_event_data=nullptr);
            void activate_primary_action();
            void move_cursor(float distance_x=0.0, float distance_y=0.0);
         };
      }
   }
}



