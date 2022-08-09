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
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <AllegroFlare/Shader.hpp>
#include <map>
#include <set>
#include <string>
#include <vector>


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
            AllegroFlare::InventoryIndex inventory_index;
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
            AllegroFlare::Shader* room_shader;
            bool initialized;
            AllegroFlare::Elements::DialogBoxes::Base* active_dialog;
            bool paused;
            std::set<std::string> subscribed_to_game_event_names;

         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::AudioController* audio_controller=nullptr);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_audio_controller(AllegroFlare::AudioController* audio_controller);
            void set_room_shader(AllegroFlare::Shader* room_shader);
            AllegroFlare::Shader* get_room_shader();
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper &get_entity_collection_helper_ref();
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            std::set<std::string> get_subscribed_to_game_event_names();
            bool is_subscribed_to_game_event_name(std::string game_event_name="[unset-game_event_name]");
            void initialize();
            void load_from_configuration_and_start(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration={});
            void load_gametest_configuration_and_start();
            void update();
            bool enter_room(std::string room_name="[unset-room_name]");
            void unhover_any_and_all_entities();
            void reset_cursors_to_default_in_all_rooms();
            std::string get_current_room_dictionary_name(AllegroFlare::Prototypes::FixedRoom2D::Room* room=nullptr);
            void render();
            void process_subscribed_to_game_event(AllegroFlare::GameEvent* game_event=nullptr);
            void process_interaction_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void render_entities_in_current_room();
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> get_entities_in_current_room();
            std::string get_dictionary_name_of_current_room();
            void update_all_rooms();
            void suspend_all_rooms();
            void resume_all_rooms();
            void pause_game();
            void unpause_game();
            void show_inventory();
            void hide_inventory();
            void toggle_inventory();
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



