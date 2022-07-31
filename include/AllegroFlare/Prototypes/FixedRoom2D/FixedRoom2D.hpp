#pragma once


#include <AllegroFlare/AudioController.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/Elements/Inventory.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <map>
#include <set>
#include <string>


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
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> room_dictionary;
            std::map<std::string, std::string> entity_room_associations;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> script_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_runner;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Room* current_room;
            bool initialized;
            AllegroFlare::Elements::DialogBoxes::Base* active_dialog;
            std::set<std::string> subscribed_to_game_event_names;

         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::AudioController* audio_controller=nullptr);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_audio_controller(AllegroFlare::AudioController* audio_controller);
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            std::set<std::string> get_subscribed_to_game_event_names();
            bool is_subscribed_to_game_event_name(std::string game_event_name="[unset-game_event_name]");
            void initialize();
            void load_story_and_start();
            void update();
            bool enter_room(std::string room_name="[unset-room_name]");
            void render();
            void process_subscribed_to_game_event(AllegroFlare::GameEvent* game_event=nullptr);
            void process_interaction_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void update_all_rooms();
            void suspend_all_rooms();
            void resume_all_rooms();
            void show_inventory();
            void hide_inventory();
            void toggle_inventory();
            void spawn_dialog_box();
            void advance_dialog();
            bool dialog_is_finished();
            bool shutdown_dialog();
            void activate_primary_action();
            void move_cursor_up();
            void move_cursor_down();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor(float distance_x=0.0, float distance_y=0.0);
         };
      }
   }
}



